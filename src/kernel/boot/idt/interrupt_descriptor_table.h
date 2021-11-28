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
#include "kernel/klibc/array.h"

namespace kernel::boot::idt {

    struct IdtPointer {
        uint16_t size;
        const InterruptDescriptor* pointer;
    } __attribute__((packed));

    void initializeInterruptDescriptorTable();

    extern "C" void loadIdtTable(const IdtPointer* pointer);

    extern "C" int fireException0();
    extern "C" int fireException1();
    extern "C" int fireException2();
    extern "C" int fireException3();
    extern "C" int fireException4();
    extern "C" int fireException5();
    extern "C" int fireException6();
    extern "C" int fireException7();
    extern "C" int fireException8();
    extern "C" int fireException9();
    extern "C" int fireException10();
    extern "C" int fireException11();
    extern "C" int fireException12();
    extern "C" int fireException13();
    extern "C" int fireException14();
    extern "C" int fireException15();
    extern "C" int fireException16();
    extern "C" int fireException17();
    extern "C" int fireException18();
    extern "C" int fireException19();
    extern "C" int fireException20();
    extern "C" int fireException21();
    extern "C" int fireException22();
    extern "C" int fireException23();
    extern "C" int fireException24();
    extern "C" int fireException25();
    extern "C" int fireException26();
    extern "C" int fireException27();
    extern "C" int fireException28();
    extern "C" int fireException29();
    extern "C" int fireException30();
    extern "C" int fireException31();

    extern "C" int fireInterruptRequest0();
    extern "C" int fireInterruptRequest1();
    extern "C" int fireInterruptRequest2();
    extern "C" int fireInterruptRequest3();
    extern "C" int fireInterruptRequest4();
    extern "C" int fireInterruptRequest5();
    extern "C" int fireInterruptRequest6();
    extern "C" int fireInterruptRequest7();
    extern "C" int fireInterruptRequest8();
    extern "C" int fireInterruptRequest9();
    extern "C" int fireInterruptRequest10();
    extern "C" int fireInterruptRequest11();
    extern "C" int fireInterruptRequest12();
    extern "C" int fireInterruptRequest13();
    extern "C" int fireInterruptRequest14();
    extern "C" int fireInterruptRequest15();
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_TABLE_H
