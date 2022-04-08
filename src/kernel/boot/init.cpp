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

#include "gdt/global_descriptor_table.h"
#include "idt/interrupt_descriptor_table.h"
#include "boot/paging/paging.h"
#include "boot/grub/multiboot_info.h"
#include "drivers/video_buffer_display.h"
#include "terminal/Terminal.h"
#include "boot/idt/pic/programmable_interrupt_controller.h"
#include "boot/tss/task_state_segment.h"
#include "boot/grub/memory_map.h"
#include "boot_info.h"
#include "library/LibDebug/include/debug.h"

namespace kernel::boot {

    static const VideoBufferDisplay display { };

    extern "C" uint32_t * kernelPageTable;

    constexpr uint8_t interruptRequestOffset = 32;

    extern "C" void init(
            MultiBootInfo * info,
            uint32_t /* magic */,
            uint32_t stackPointer,
            BootInfo bootInfo
    ) {

        // todo: move kernel to higher half?
        // todo: verify paging is on

        lib::debug::magicBreakPoint();

        paging::setupPaging(
                bootInfo.pageDirectory,
                bootInfo.kernelPageTable,
                0xC0000000,
                bootInfo.kernelStartAddress,
                bootInfo.kernelEndAddress
        );

        lib::debug::magicBreakPoint();

        // Construct memory map from grub multiboot information passed from grub
        grub::constructMemoryMap(info);

        // todo: replace with log stream? pass to root process?
        auto terminal = Terminal{display};

        terminal.clear();
        terminal.println("System init");

        auto tssDescriptor = tss::getTaskStateSegmentDescriptor();
        gdt::initializeGlobalDescriptorTable(tssDescriptor);
        terminal.println("Global Descriptor table initialized");

        //
        tss::initializeTaskStateSegment(stackPointer);
        terminal.println("Task State Segment initialized");

        //
        idt::initializeInterruptDescriptorTable();
        terminal.println("Interrupt Descriptor table initialized");

        // todo: may need to be moved to init protected method?
        //
        idt::remapProgrammableInterruptController(
                interruptRequestOffset,
                interruptRequestOffset + 8
        );
    }
}