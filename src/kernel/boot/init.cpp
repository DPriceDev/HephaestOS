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

#include <cstdint>
#include <format.h>

#include "gdt/global_descriptor_table.h"
#include "idt/interrupt_descriptor_table.h"
#include "paging/paging.h"
#include "grub/multiboot_info.h"
#include "idt/pic/programmable_interrupt_controller.h"
#include "tss/task_state_segment.h"
#include "grub/memory_map.h"
#include "serial/serial_port.h"
#include "boot_info.h"
#include "elf.h"
#include "elf/elf_header.h"
#include "memory/boot_allocator.h"
#include "memory/new.h"
#include "string.h"

namespace kernel::boot {

    extern "C" void kernelMain();

    extern "C" void loadKernelSegment();

    extern "C" void enableInterrupts();

    extern "C" void disableInterrupts();

    constexpr uint8_t interruptRequestOffset = 32;

    static const SerialPortConnection connection { SerialPort::COM1 };

    uintptr_t loadKernelModule(MultiBootInfo* pInfo, BootInfo info);

    extern "C" void init(
            MultiBootInfo * info,
            uint32_t magic,
            uint32_t stackPointer,
            BootInfo bootInfo
    ) {
        const auto bootSize = bootInfo.kernelEndAddress - bootInfo.kernelStartAddress;
        BootAllocator::getInstance().setMemoryPointer(
            bootInfo.kernelEndAddress,
            bootInfo.kernelVirtualAddress + bootSize
        );

        if (connection.open()) {
            std::KernelFormatOutput::getInstance().setStandardOutputIterator(
                std::StandardOutputIterator {
                    &connection,
                    [] (const void* pointer) { },
                    [] (const void* pointer, char character) {
                        static_cast<const SerialPortConnection*>(pointer)->write(character);
                    },
                    [] (const void* pointer) { },
                }
            );
        }

        std::print("System init\n");
        // Construct memory map from grub multiboot information passed from grub
    //        grub::constructMemoryMap(info);

        auto tssDescriptor = tss::getTaskStateSegmentDescriptor();
        gdt::initializeGlobalDescriptorTable(tssDescriptor);
        std::print("Global Descriptor table initialized\n");

        //
        tss::initializeTaskStateSegment(stackPointer);
        std::print("Task State Segment initialized\n");

        //
        idt::initializeInterruptDescriptorTable();
        std::print("Interrupt Descriptor table initialized\n");

        // todo: move register addresses to header of idt
        idt::remapProgrammableInterruptController(
            interruptRequestOffset,
            interruptRequestOffset + 8
        );
        std::print("Interrupts remapped\n");

        auto kernelAddress = loadKernelModule(info, bootInfo);

        typedef void (*EnterKernel)();
        EnterKernel enterKernel = reinterpret_cast<EnterKernel>(kernelAddress);

        paging::unmapLowerKernel(bootInfo.pageDirectory);

        loadKernelSegment();
        enableInterrupts();
        enterKernel();

        disableInterrupts();
    }

    void loadElfToMemory(uintptr_t header);

    uintptr_t loadKernelModule(MultiBootInfo* info, BootInfo bootInfo) {
        std::print("Loading Kernel Module\n");

        if (info->moduleCount == 0) {
            std::print("No Modules Found\n");
            return 0;
        }

        auto& kernelModule = info->modulePtr[0];

        // todo: map kernel module memory to page table

        // todo: Align to page

        const auto elfAddress = kernelModule.moduleStart + bootInfo.kernelVirtualAddress;
        loadElfToMemory(kernelModule.moduleStart + bootInfo.kernelVirtualAddress);

        auto t = 0;

        // todo: Return entry address?

        auto* elfHeader = reinterpret_cast<Elf32_Ehdr*>(elfAddress);
        return elfHeader->e_entry;
    }


    void loadElfToMemory(uintptr_t elfPointer) {
        auto* elfHeader = reinterpret_cast<Elf32_Ehdr*>(elfPointer);
        auto* programHeader = reinterpret_cast<Elf32_Phdr*>(elfPointer + elfHeader->e_phoff);
        auto programHeaders = std::Span<Elf32_Phdr>(programHeader, elfHeader->e_phnum);

        for (const auto & header : programHeaders) {
            const auto programAddress = reinterpret_cast<void*>(elfPointer + header.p_offset);
            const auto memoryAddress = reinterpret_cast<void*>(header.p_vaddr);
            memset(memoryAddress, 0, header.p_memsz);
            memcpy(memoryAddress, programAddress, header.p_filesz);
        }
    }
}