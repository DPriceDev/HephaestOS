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

#include "gdt/global_descriptor_table.h"
#include "idt/interrupt_descriptor_table.h"
#include "kernel/lib/libc/stdoffset.h"
#include "kernel/boot/grub/multiboot_info.h"
#include <kernel/drivers/video_buffer_display.h>
#include "kernel/terminal/Terminal.h"
#include "kernel/boot/idt/pic/programmable_interrupt_controller.h"
#include "kernel/boot/tss/task_state_segment.h"

namespace kernel::boot {

    static const VideoBufferDisplay display { };

    constexpr uint8_t interruptRequestOffset = 32;

    extern "C" void init(MultiBootInfo * info, uint32_t /* magic */, uint32_t stackPointer) {
        auto terminal = Terminal{display};

        terminal.clear();
        terminal.println("System init");

        // todo: Setup paging

        //
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

        // todo: call global descriptors
    }
}