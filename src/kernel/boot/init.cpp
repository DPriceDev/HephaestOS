/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <bit>
#include <boot_info.h>
#include <elf.h>
#include <elf/boot_elf_loader.h>
#include <format.h>
#include <gdt/global_descriptor_table.h>
#include <idt/interrupt_descriptor_table.h>
#include <idt/pic/programmable_interrupt_controller.h>
#include <memory/boot_allocator.h>
#include <paging/paging.h>
#include <serial_port.h>
#include <tss/task_state_segment.h>

namespace kernel::boot {

    extern "C" void loadKernelSegment();

    extern "C" void enableInterrupts();

    extern "C" void disableInterrupts();

    static const debug::SerialPortConnection connection { debug::SerialPort::COM1 };

    auto loadModules(const MultiBootInfo* info, const BootInfo& bootInfo) -> std::Result<uintptr_t>;

    void initializeBootAllocator(const BootInfo& bootInfo);

    void initializeSerialPort();

    void initializeDescriptorTables(uint32_t stackPointer);

    void setupInterrupts();

    void enterKernelModule(const std::Result<uintptr_t>& kernelAddress);

    struct LoadedModule {
        std::StringView name;
        uintptr_t address;
    };

    auto loadBootModule(const BootInfo& bootInfo, const ModuleEntry& bootModule) -> std::Result<LoadedModule>;

    extern "C" void init(
            MultiBootInfo * info,
            uint32_t magic,
            uint32_t stackPointer,
            BootInfo bootInfo
    ) {
        initializeSerialPort();
        std::print("System init\n");

        initializeBootAllocator(bootInfo);

        initializeDescriptorTables(stackPointer);

        setupInterrupts();

        if (info->moduleCount == 0) {
            std::print("No Boot Modules Found\n");
            return;
        }


        const auto kernelAddress = loadModules(info, bootInfo);

        paging::unmapLowerKernel(bootInfo.pageDirectory);

        if (kernelAddress.isValid()) {
            std::print("Entering kernel module\n");
            enterKernelModule(kernelAddress);
        } else {
            std::print("Failed to enter kernel module\n");
        }
    }

    void enterKernelModule(const std::Result<uintptr_t>& kernelAddress) {
        typedef void (*EnterKernel)(const std::StandardOutputIterator&);
        EnterKernel enterKernel = std::bit_cast<EnterKernel>(kernelAddress.get());
        const auto& interator = std::KernelFormatOutput::getInstance().out();
        loadKernelSegment();
        enableInterrupts();
        enterKernel(interator);
        disableInterrupts();
    }

    void setupInterrupts() {
        constexpr uint8_t masterDeviceOffset = 32;
        constexpr uint8_t slaveDeviceOffset = masterDeviceOffset + 8;
        idt::remapProgrammableInterruptController(masterDeviceOffset,slaveDeviceOffset);
        std::print("Interrupts remapped\n");
    }

    void initializeDescriptorTables(uint32_t stackPointer) {
        auto tssDescriptor = tss::getTaskStateSegmentDescriptor();
        gdt::initializeGlobalDescriptorTable(tssDescriptor);
        std::print("Global Descriptor table initialized\n");

        tss::initializeTaskStateSegment(stackPointer);
        std::print("Task State Segment initialized\n");

        idt::initializeInterruptDescriptorTable();
        std::print("Interrupt Descriptor table initialized\n");
    }

    void initializeSerialPort() {
        if (connection.open()) {
            std::KernelFormatOutput::getInstance().setStandardOutputIterator(
                std::StandardOutputIterator {
                    &connection,
                    [] (const void* pointer) { },
                    [] (const void* pointer, char character) {
                        static_cast<const debug::SerialPortConnection*>(pointer)->write(character);
                    },
                    [] (const void* pointer) { },
                }
            );
        }
    }

    void initializeBootAllocator(const BootInfo& bootInfo) {
        const auto bootSize = bootInfo.kernelEndAddress - bootInfo.kernelStartAddress;
        BootAllocator::getInstance().setMemoryPointer(
            bootInfo.kernelEndAddress,
            bootInfo.kernelVirtualAddress + bootSize
        );
        std::print("Early Boot Allocator initialized\n");
    }

    auto loadModules(const MultiBootInfo* info, const BootInfo& bootInfo) -> std::Result<uintptr_t> {
        std::print("Loading {} Boot Module{}\n", info->moduleCount, (info->moduleCount == 1) ? "" : "s");

        uintptr_t kernelAddress = 0; // todo: Optional or replace with list of modules

        const auto bootModules = std::Span<ModuleEntry> { info->modulePtr, info->moduleCount };
        for (const auto& bootModule: bootModules) {
            const auto loadedModule = loadBootModule(bootInfo, bootModule);

            // todo: maybe just return a list of pairs of module name and address
            if (loadedModule.isValid() && loadedModule.get().name == "kernel") {
                kernelAddress = loadedModule.get().address;
            }
        }

        if (kernelAddress == 0) {
            return std::Result<uintptr_t>::failure();
        }

        return std::Result<uintptr_t>::success(kernelAddress);
    }

    auto loadBootModule(const BootInfo& bootInfo, const ModuleEntry& bootModule) -> std::Result<LoadedModule> {
        const auto moduleName = std::StringView { std::bit_cast<char*>(bootModule.string + bootInfo.kernelVirtualAddress) };
        std::print("Loading Boot Module: {}\n", moduleName);

        const auto elfAddress = bootModule.moduleStart + bootInfo.kernelVirtualAddress;
        const auto elfInfoResult = elf::getElfInfo(elfAddress);

        if (elfInfoResult.isNotValid()) {
            std::print("Failed to load boot module: {}\n", moduleName);
            return std::Result<LoadedModule>::failure();
        }
        elf::ElfInfo elfInfo = elfInfoResult.get();

        // todo: map boot module memory (alignment)

        const auto entryAddress = std::visit(
            std::Visitors {
                [] (const std::Result<elf::RelocatableElf>&& elf) {
                    const auto address = 0xC0300000;
                    elf::loadElf(elf.get(), address);
                    return address;
                },
                [] (const std::Result<elf::ExecutableElf>&& elf) {
                    elf::loadElf(elf.get());
                    return elf.get().entryAddress;
                }
            },
            elfInfo
        );

        return std::Result<LoadedModule>::success({ moduleName, entryAddress });
    }
}