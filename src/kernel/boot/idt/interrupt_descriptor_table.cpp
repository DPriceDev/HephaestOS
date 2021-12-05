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

    InterruptDescriptor constructInterruptDescriptor(int (*handler)(), uint8_t type) {
        return InterruptDescriptor {
                static_cast<uint16_t>((uint32_t) handler & 0xFFFF),
                0x08,
                0,
                TypeAttributes {
                        type, 0, 0, 1
                },
                static_cast<uint16_t>(((uint32_t) handler >> 16) & 0xFFFF)
        };
    }

    void initializeInterruptDescriptorTable() {
        interruptDescriptorTable.at(0)  = constructInterruptDescriptor(fireException0,0xF);
        interruptDescriptorTable.at(1)  = constructInterruptDescriptor(fireException1, 0xF);
        interruptDescriptorTable.at(2)  = constructInterruptDescriptor(fireException2, 0xF);
        interruptDescriptorTable.at(3)  = constructInterruptDescriptor(fireException3, 0xF);
        interruptDescriptorTable.at(4)  = constructInterruptDescriptor(fireException4, 0xF);
        interruptDescriptorTable.at(5)  = constructInterruptDescriptor(fireException5, 0xF);
        interruptDescriptorTable.at(6)  = constructInterruptDescriptor(fireException6, 0xF);
        interruptDescriptorTable.at(7)  = constructInterruptDescriptor(fireException7, 0xF);
        interruptDescriptorTable.at(8)  = constructInterruptDescriptor(fireException8, 0xF);
        interruptDescriptorTable.at(9)  = constructInterruptDescriptor(fireException9, 0xF);
        interruptDescriptorTable.at(10) = constructInterruptDescriptor(fireException10, 0xF);
        interruptDescriptorTable.at(11) = constructInterruptDescriptor(fireException11, 0xF);
        interruptDescriptorTable.at(12) = constructInterruptDescriptor(fireException12, 0xF);
        interruptDescriptorTable.at(13) = constructInterruptDescriptor(fireException13, 0xF);
        interruptDescriptorTable.at(14) = constructInterruptDescriptor(fireException14, 0xF);
        interruptDescriptorTable.at(15) = constructInterruptDescriptor(fireException15, 0xF);
        interruptDescriptorTable.at(16) = constructInterruptDescriptor(fireException16, 0xF);
        interruptDescriptorTable.at(17) = constructInterruptDescriptor(fireException17, 0xF);
        interruptDescriptorTable.at(18) = constructInterruptDescriptor(fireException18, 0xF);
        interruptDescriptorTable.at(19) = constructInterruptDescriptor(fireException19, 0xF);
        interruptDescriptorTable.at(20) = constructInterruptDescriptor(fireException20, 0xF);
        interruptDescriptorTable.at(21) = constructInterruptDescriptor(fireException21, 0xF);
        interruptDescriptorTable.at(22) = constructInterruptDescriptor(fireException22, 0xF);
        interruptDescriptorTable.at(23) = constructInterruptDescriptor(fireException23, 0xF);
        interruptDescriptorTable.at(24) = constructInterruptDescriptor(fireException24, 0xF);
        interruptDescriptorTable.at(25) = constructInterruptDescriptor(fireException25, 0xF);
        interruptDescriptorTable.at(26) = constructInterruptDescriptor(fireException26, 0xF);
        interruptDescriptorTable.at(27) = constructInterruptDescriptor(fireException27, 0xF);
        interruptDescriptorTable.at(28) = constructInterruptDescriptor(fireException28, 0xF);
        interruptDescriptorTable.at(29) = constructInterruptDescriptor(fireException29, 0xF);
        interruptDescriptorTable.at(30) = constructInterruptDescriptor(fireException30, 0xF);
        interruptDescriptorTable.at(31) = constructInterruptDescriptor(fireException31, 0xF);
        interruptDescriptorTable.at(32) = constructInterruptDescriptor(fireInterruptRequest0, 0xE);
        interruptDescriptorTable.at(33) = constructInterruptDescriptor(fireInterruptRequest1, 0xE);
        interruptDescriptorTable.at(34) = constructInterruptDescriptor(fireInterruptRequest2, 0xE);
        interruptDescriptorTable.at(35) = constructInterruptDescriptor(fireInterruptRequest3, 0xE);
        interruptDescriptorTable.at(36) = constructInterruptDescriptor(fireInterruptRequest4, 0xE);
        interruptDescriptorTable.at(37) = constructInterruptDescriptor(fireInterruptRequest5, 0xE);
        interruptDescriptorTable.at(38) = constructInterruptDescriptor(fireInterruptRequest6, 0xE);
        interruptDescriptorTable.at(39) = constructInterruptDescriptor(fireInterruptRequest7, 0xE);
        interruptDescriptorTable.at(40) = constructInterruptDescriptor(fireInterruptRequest8, 0xE);
        interruptDescriptorTable.at(41) = constructInterruptDescriptor(fireInterruptRequest9, 0xE);
        interruptDescriptorTable.at(42) = constructInterruptDescriptor(fireInterruptRequest10, 0xE);
        interruptDescriptorTable.at(43) = constructInterruptDescriptor(fireInterruptRequest11, 0xE);
        interruptDescriptorTable.at(44) = constructInterruptDescriptor(fireInterruptRequest12, 0xE);
        interruptDescriptorTable.at(45) = constructInterruptDescriptor(fireInterruptRequest13, 0xE);
        interruptDescriptorTable.at(46) = constructInterruptDescriptor(fireInterruptRequest14, 0xE);
        interruptDescriptorTable.at(47) = constructInterruptDescriptor(fireInterruptRequest15, 0xE);

        idtPointer = {
                (sizeof(InterruptDescriptor) * tableLength) - 1,
                interruptDescriptorTable.data()
        };

        loadIdtTable(&idtPointer);
    }
}