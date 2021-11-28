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

#include "interrupt_descriptor_table.h"

namespace kernel::boot::idt {
    constexpr uint32_t tableLength = 256;

    Array<InterruptDescriptor, tableLength> interruptDescriptorTable;

    IdtPointer idtPointer;

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

    void initializeInterruptDescriptorTable() {
        interruptDescriptorTable.at(0)  = constructInterruptDescriptor(fireException0);
        interruptDescriptorTable.at(1)  = constructInterruptDescriptor(fireException1);
        interruptDescriptorTable.at(2)  = constructInterruptDescriptor(fireException2);
        interruptDescriptorTable.at(3)  = constructInterruptDescriptor(fireException3);
        interruptDescriptorTable.at(4)  = constructInterruptDescriptor(fireException4);
        interruptDescriptorTable.at(5)  = constructInterruptDescriptor(fireException5);
        interruptDescriptorTable.at(6)  = constructInterruptDescriptor(fireException6);
        interruptDescriptorTable.at(7)  = constructInterruptDescriptor(fireException7);
        interruptDescriptorTable.at(8)  = constructInterruptDescriptor(fireException8);
        interruptDescriptorTable.at(9)  = constructInterruptDescriptor(fireException9);
        interruptDescriptorTable.at(10) = constructInterruptDescriptor(fireException10);
        interruptDescriptorTable.at(11) = constructInterruptDescriptor(fireException11);
        interruptDescriptorTable.at(12) = constructInterruptDescriptor(fireException12);
        interruptDescriptorTable.at(13) = constructInterruptDescriptor(fireException13);
        interruptDescriptorTable.at(14) = constructInterruptDescriptor(fireException14);
        interruptDescriptorTable.at(15) = constructInterruptDescriptor(fireException15);
        interruptDescriptorTable.at(16) = constructInterruptDescriptor(fireException16);
        interruptDescriptorTable.at(17) = constructInterruptDescriptor(fireException17);
        interruptDescriptorTable.at(18) = constructInterruptDescriptor(fireException18);
        interruptDescriptorTable.at(19) = constructInterruptDescriptor(fireException19);
        interruptDescriptorTable.at(20) = constructInterruptDescriptor(fireException20);
        interruptDescriptorTable.at(21) = constructInterruptDescriptor(fireException21);
        interruptDescriptorTable.at(22) = constructInterruptDescriptor(fireException22);
        interruptDescriptorTable.at(23) = constructInterruptDescriptor(fireException23);
        interruptDescriptorTable.at(24) = constructInterruptDescriptor(fireException24);
        interruptDescriptorTable.at(25) = constructInterruptDescriptor(fireException25);
        interruptDescriptorTable.at(26) = constructInterruptDescriptor(fireException26);
        interruptDescriptorTable.at(27) = constructInterruptDescriptor(fireException27);
        interruptDescriptorTable.at(28) = constructInterruptDescriptor(fireException28);
        interruptDescriptorTable.at(29) = constructInterruptDescriptor(fireException29);
        interruptDescriptorTable.at(30) = constructInterruptDescriptor(fireException30);
        interruptDescriptorTable.at(31) = constructInterruptDescriptor(fireException31);
        interruptDescriptorTable.at(32) = constructInterruptDescriptor(fireInterruptRequest0);
        interruptDescriptorTable.at(33) = constructInterruptDescriptor(fireInterruptRequest1);
        interruptDescriptorTable.at(34) = constructInterruptDescriptor(fireInterruptRequest2);
        interruptDescriptorTable.at(35) = constructInterruptDescriptor(fireInterruptRequest3);
        interruptDescriptorTable.at(36) = constructInterruptDescriptor(fireInterruptRequest4);
        interruptDescriptorTable.at(37) = constructInterruptDescriptor(fireInterruptRequest5);
        interruptDescriptorTable.at(38) = constructInterruptDescriptor(fireInterruptRequest6);
        interruptDescriptorTable.at(39) = constructInterruptDescriptor(fireInterruptRequest7);
        interruptDescriptorTable.at(40) = constructInterruptDescriptor(fireInterruptRequest8);
        interruptDescriptorTable.at(41) = constructInterruptDescriptor(fireInterruptRequest9);
        interruptDescriptorTable.at(42) = constructInterruptDescriptor(fireInterruptRequest10);
        interruptDescriptorTable.at(43) = constructInterruptDescriptor(fireInterruptRequest11);
        interruptDescriptorTable.at(44) = constructInterruptDescriptor(fireInterruptRequest12);
        interruptDescriptorTable.at(45) = constructInterruptDescriptor(fireInterruptRequest13);
        interruptDescriptorTable.at(46) = constructInterruptDescriptor(fireInterruptRequest14);
        interruptDescriptorTable.at(47) = constructInterruptDescriptor(fireInterruptRequest15);

        idtPointer = {
                (sizeof(InterruptDescriptor) * tableLength) - 1,
                interruptDescriptorTable.data()
        };

        loadIdtTable(&idtPointer);
    }
}