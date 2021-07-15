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

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_TABLE_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_TABLE_H

#include <kernel/drivers/video_buffer_display.h>
#include <kernel/terminal/Terminal.h>
#include "kernel/types.h"
#include "interupt_descriptor.h"
#include "hardware/io.h"

namespace kernel::boot::idt {

    extern "C" void loadIdtTable(uint32_t pointer);

    extern "C" int irq0();

    constexpr InterruptDescriptor constructInterruptDescriptor(uint32_t handler) {
        InterruptDescriptor descriptor {
                static_cast<uint16_t>(handler & 0xFFFF),
                0x08,
                0,
                TypeAttributes {
                    14, 0, 1, 1
                },
                static_cast<uint16_t>((handler >> 16) & 0xFFFF)
        };

        return descriptor;
    }

    struct IdtPointer {
        uint16_t size;
        uint32_t pointer;
    } __attribute__((packed));

    InterruptDescriptor interruptDescriptorTable[256];

    const IdtPointer idtPointer {
            (sizeof(InterruptDescriptor) * 256) - 1,
            (uint32_t) interruptDescriptorTable
    };

    void initializeInterruptDescriptorTable() {
        interruptDescriptorTable[0] = constructInterruptDescriptor((uint32_t) irq0);
        interruptDescriptorTable[1] = constructInterruptDescriptor((uint32_t) irq0);
        loadIdtTable((uint32_t) &idtPointer);
    }
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_TABLE_H
