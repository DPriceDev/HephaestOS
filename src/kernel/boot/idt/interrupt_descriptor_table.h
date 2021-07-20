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

    struct IdtPointer {
        const uint16_t size;
        const InterruptDescriptor* pointer;
    } __attribute__((packed));

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

    InterruptDescriptor constructInterruptDescriptor(int (*handler)()) {
        return InterruptDescriptor {
                static_cast<uint16_t>((uint32_t) handler & 0xFFFF),
                0x08,
                0,
                TypeAttributes {
                    14, 0, 1, 1
                },
                static_cast<uint16_t>(((uint32_t) handler >> 16) & 0xFFFF)
        };
    }

    InterruptDescriptor interruptDescriptorTable[256];

    constexpr IdtPointer idtPointer {
            (sizeof(InterruptDescriptor) * 256) - 1,
            interruptDescriptorTable
    };

    void initializeInterruptDescriptorTable() {
        interruptDescriptorTable[0]     = constructInterruptDescriptor(fireException0);
        interruptDescriptorTable[1]     = constructInterruptDescriptor(fireException1);
        interruptDescriptorTable[2]     = constructInterruptDescriptor(fireException2);
        interruptDescriptorTable[3]     = constructInterruptDescriptor(fireException3);
        interruptDescriptorTable[4]     = constructInterruptDescriptor(fireException4);
        interruptDescriptorTable[5]     = constructInterruptDescriptor(fireException5);
        interruptDescriptorTable[6]     = constructInterruptDescriptor(fireException6);
        interruptDescriptorTable[7]     = constructInterruptDescriptor(fireException7);
        interruptDescriptorTable[8]     = constructInterruptDescriptor(fireException8);
        interruptDescriptorTable[9]     = constructInterruptDescriptor(fireException9);
        interruptDescriptorTable[10]    = constructInterruptDescriptor(fireException10);
        interruptDescriptorTable[11]    = constructInterruptDescriptor(fireException11);
        interruptDescriptorTable[12]    = constructInterruptDescriptor(fireException12);
        interruptDescriptorTable[13]    = constructInterruptDescriptor(fireException13);
        interruptDescriptorTable[14]    = constructInterruptDescriptor(fireException14);
        interruptDescriptorTable[15]    = constructInterruptDescriptor(fireException15);
        interruptDescriptorTable[16]    = constructInterruptDescriptor(fireException16);
        interruptDescriptorTable[17]    = constructInterruptDescriptor(fireException17);
        interruptDescriptorTable[18]    = constructInterruptDescriptor(fireException18);
        interruptDescriptorTable[19]    = constructInterruptDescriptor(fireException19);
        interruptDescriptorTable[20]    = constructInterruptDescriptor(fireException20);
        interruptDescriptorTable[21]    = constructInterruptDescriptor(fireException21);
        interruptDescriptorTable[22]    = constructInterruptDescriptor(fireException22);
        interruptDescriptorTable[23]    = constructInterruptDescriptor(fireException23);
        interruptDescriptorTable[24]    = constructInterruptDescriptor(fireException24);
        interruptDescriptorTable[25]    = constructInterruptDescriptor(fireException25);
        interruptDescriptorTable[26]    = constructInterruptDescriptor(fireException26);
        interruptDescriptorTable[27]    = constructInterruptDescriptor(fireException27);
        interruptDescriptorTable[28]    = constructInterruptDescriptor(fireException28);
        interruptDescriptorTable[29]    = constructInterruptDescriptor(fireException29);
        interruptDescriptorTable[30]    = constructInterruptDescriptor(fireException30);
        interruptDescriptorTable[31]    = constructInterruptDescriptor(fireException31);
        interruptDescriptorTable[32]    = constructInterruptDescriptor(fireInterruptRequest0);
        interruptDescriptorTable[33]    = constructInterruptDescriptor(fireInterruptRequest1);
        interruptDescriptorTable[34]    = constructInterruptDescriptor(fireInterruptRequest2);
        interruptDescriptorTable[35]    = constructInterruptDescriptor(fireInterruptRequest3);
        interruptDescriptorTable[36]    = constructInterruptDescriptor(fireInterruptRequest4);
        interruptDescriptorTable[37]    = constructInterruptDescriptor(fireInterruptRequest5);
        interruptDescriptorTable[38]    = constructInterruptDescriptor(fireInterruptRequest6);
        interruptDescriptorTable[39]    = constructInterruptDescriptor(fireInterruptRequest7);
        interruptDescriptorTable[40]    = constructInterruptDescriptor(fireInterruptRequest8);
        interruptDescriptorTable[41]    = constructInterruptDescriptor(fireInterruptRequest9);
        interruptDescriptorTable[42]    = constructInterruptDescriptor(fireInterruptRequest10);
        interruptDescriptorTable[43]    = constructInterruptDescriptor(fireInterruptRequest11);
        interruptDescriptorTable[44]    = constructInterruptDescriptor(fireInterruptRequest12);
        interruptDescriptorTable[45]    = constructInterruptDescriptor(fireInterruptRequest13);
        interruptDescriptorTable[46]    = constructInterruptDescriptor(fireInterruptRequest14);
        interruptDescriptorTable[47]    = constructInterruptDescriptor(fireInterruptRequest15);

        loadIdtTable(&idtPointer);
    }
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_TABLE_H
