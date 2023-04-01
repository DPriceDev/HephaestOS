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
#include <format.h>
#include <gdt/global_descriptor_table.h>
#include <idt/interrupt_descriptor_table.h>
#include <idt/pic/programmable_interrupt_controller.h>
#include <init.h>
#include <memory/boot_allocator.h>
#include <modules/module_loader.h>
#include <serial_port.h>
#include <tss/task_state_segment.h>

extern "C" void init(boot::MultiBootInfo& info, uint32_t magic, uint32_t stackPointer, boot::BootInfo bootInfo) {
    boot::initializeSerialPort();
    std::print("INFO: System init\n");

    constexpr uint32_t MULTIBOOT_ONE_MAGIC_NUMBER = 0x2BADB002;
    if (magic != MULTIBOOT_ONE_MAGIC_NUMBER) {
        std::print("ERROR: Multiboot magic number is not correct.\n");
        return;
    }

    boot::initializeDescriptorTables(stackPointer);

    const auto bootModules = std::Span<boot::ModuleEntry> { info.modulePtr, info.moduleCount };
    const auto nextAvailableMemory = findNextAvailableMemory(bootModules, bootInfo);

    auto allocator = boot::BootAllocator(bootInfo.virtualBase, nextAvailableMemory, bootInfo.pageTable);
    const auto kernelAddress = loadModules(bootModules, allocator, bootInfo);

    boot::unmapLowerKernel(bootInfo.pageDirectory);

    if (!kernelAddress) {
        std::print("ERROR: Failed to enter kernel module\n");
        return;
    }
    boot::enterKernelModule(stackPointer, kernelAddress.value(), info, bootInfo, allocator);
}

namespace boot {
    static const debug::SerialPortConnection connection { debug::SerialPort::COM1 };

    void initializeSerialPort() {
        if (connection.open()) {
            std::KernelFormatOutput::getInstance().setStandardOutputIterator(std::StandardOutputIterator {
                &connection,
                [](const void*) { /* Serial port cannot be de-referenced. */ },
                [](const void* pointer, char character) {
                    // todo: std::any here?
                    static_cast<const debug::SerialPortConnection*>(pointer)->write(character);
                },
                [](const void*) { /* Serial Port self increments. */ },
            });
        }
    }

    void initializeDescriptorTables(uint32_t stackPointer) {
        auto tssDescriptor = getTaskStateSegmentDescriptor();
        initializeGlobalDescriptorTable(tssDescriptor);
        std::print("INFO: Global Descriptor table initialized\n");

        initializeTaskStateSegment(stackPointer);
        std::print("INFO: Task State Segment initialized\n");

        initializeInterruptDescriptorTable();
        std::print("INFO: Interrupt Descriptor table initialized\n");

        setupInterrupts();
    }

    void setupInterrupts() {
        constexpr uint8_t masterDeviceOffset = 32;
        constexpr uint8_t slaveDeviceOffset = masterDeviceOffset + 8;
        remapProgrammableInterruptController(masterDeviceOffset, slaveDeviceOffset);
        std::print("INFO: Interrupts remapped\n");
    }

    auto findNextAvailableMemory(const std::Span<ModuleEntry>& bootModules, const BootInfo& bootInfo) -> uintptr_t {
        uintptr_t address = bootInfo.bootEnd;
        for (const auto& bootModule : bootModules) {
            if (bootModule.moduleEnd > address) {
                address = bootModule.moduleEnd;
            }
        }
        return address;
    }

    void enterKernelModule(uintptr_t stackPointer, uintptr_t kernelAddress, const MultiBootInfo& multiBootInfo, const BootInfo& bootInfo, BootAllocator& allocator) {
        using EnterKernel = void (*)(
            const std::StandardOutputIterator&,
            uintptr_t,
            uintptr_t,
            const std::Span<MemoryMapEntry>*,
            PageDirectoryEntry*,
            PageTableEntry*,
            uintptr_t
        );

        const auto enterKernel = std::bit_cast<EnterKernel>(kernelAddress);
        std::print("INFO: Entering kernel module at address: {:x}\n", kernelAddress);
        const auto& output = std::KernelFormatOutput::getInstance().out();
        loadKernelSegment();
        enableInterrupts();
        const std::Span<MemoryMapEntry> memoryMap { multiBootInfo.memoryMapPtr, multiBootInfo.memoryMapLength };
        enterKernel(
            output,
            bootInfo.virtualBase,
            allocator.nextAvailableMemory(),
            &memoryMap,
            bootInfo.pageDirectory,
            bootInfo.pageTable,
            stackPointer
        );
    }
}// namespace boot