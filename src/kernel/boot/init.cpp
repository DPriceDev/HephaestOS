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

#include "kernel/boot/global_descriptor_table.h"
#include "kernel/boot/interrupt_descriptor_table.h"
#include "kernel/types.h"
#include "multiboot_info.h"
#include <kernel/drivers/video_buffer_display.h>
#include "kernel/terminal/Terminal.h"

namespace kernel {

    static const VideoBufferDisplay display { };

    extern "C" void init(MultiBootInfo * info, uint32_t /* magic */) {
        auto terminal = kernel::Terminal{display};

        terminal.clear();
        terminal.println("System init");

        gdt::initializeGlobalDescriptorTable();
        terminal.println("Global Descriptor table set");

        idt::initializeInterruptDescriptorTable();
        terminal.println("Interrupt Descriptor table set");
    }
}
