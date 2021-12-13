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

#include <kernel/lib/libc/stdint.h>

#include "interrupt_descriptor_table.h"

namespace kernel::boot::idt {

    // Array of Interrupt Descriptors that defines the Interrupt Descriptor Table.
    Array<InterruptDescriptor, tableLength> interruptDescriptorTable;

    // Structure holding the Interrupt descriptor Table array pointer and size of the array.
    IdtPointer idtPointer;

    /**
     *
     */
    void initializeInterruptDescriptorTable() {

        //
        interruptDescriptorTable.at(0)  = constructInterruptDescriptor(fireException0,GateType::Trap);
        interruptDescriptorTable.at(1)  = constructInterruptDescriptor(fireException1, GateType::Trap);
        interruptDescriptorTable.at(2)  = constructInterruptDescriptor(fireException2, GateType::Trap);
        interruptDescriptorTable.at(3)  = constructInterruptDescriptor(fireException3, GateType::Trap);
        interruptDescriptorTable.at(4)  = constructInterruptDescriptor(fireException4, GateType::Trap);
        interruptDescriptorTable.at(5)  = constructInterruptDescriptor(fireException5, GateType::Trap);
        interruptDescriptorTable.at(6)  = constructInterruptDescriptor(fireException6, GateType::Trap);
        interruptDescriptorTable.at(7)  = constructInterruptDescriptor(fireException7, GateType::Trap);
        interruptDescriptorTable.at(8)  = constructInterruptDescriptor(fireException8, GateType::Trap);
        interruptDescriptorTable.at(9)  = constructInterruptDescriptor(fireException9, GateType::Trap);
        interruptDescriptorTable.at(10) = constructInterruptDescriptor(fireException10, GateType::Trap);
        interruptDescriptorTable.at(11) = constructInterruptDescriptor(fireException11, GateType::Trap);
        interruptDescriptorTable.at(12) = constructInterruptDescriptor(fireException12, GateType::Trap);
        interruptDescriptorTable.at(13) = constructInterruptDescriptor(fireException13, GateType::Trap);
        interruptDescriptorTable.at(14) = constructInterruptDescriptor(fireException14, GateType::Trap);
        interruptDescriptorTable.at(15) = constructInterruptDescriptor(fireException15, GateType::Trap);
        interruptDescriptorTable.at(16) = constructInterruptDescriptor(fireException16, GateType::Trap);
        interruptDescriptorTable.at(17) = constructInterruptDescriptor(fireException17, GateType::Trap);
        interruptDescriptorTable.at(18) = constructInterruptDescriptor(fireException18, GateType::Trap);
        interruptDescriptorTable.at(19) = constructInterruptDescriptor(fireException19, GateType::Trap);
        interruptDescriptorTable.at(20) = constructInterruptDescriptor(fireException20, GateType::Trap);
        interruptDescriptorTable.at(21) = constructInterruptDescriptor(fireException21, GateType::Trap);
        interruptDescriptorTable.at(22) = constructInterruptDescriptor(fireException22, GateType::Trap);
        interruptDescriptorTable.at(23) = constructInterruptDescriptor(fireException23, GateType::Trap);
        interruptDescriptorTable.at(24) = constructInterruptDescriptor(fireException24, GateType::Trap);
        interruptDescriptorTable.at(25) = constructInterruptDescriptor(fireException25, GateType::Trap);
        interruptDescriptorTable.at(26) = constructInterruptDescriptor(fireException26, GateType::Trap);
        interruptDescriptorTable.at(27) = constructInterruptDescriptor(fireException27, GateType::Trap);
        interruptDescriptorTable.at(28) = constructInterruptDescriptor(fireException28, GateType::Trap);
        interruptDescriptorTable.at(29) = constructInterruptDescriptor(fireException29, GateType::Trap);
        interruptDescriptorTable.at(30) = constructInterruptDescriptor(fireException30, GateType::Trap);
        interruptDescriptorTable.at(31) = constructInterruptDescriptor(fireException31, GateType::Trap);

        //
        interruptDescriptorTable.at(32) = constructInterruptDescriptor(fireInterruptRequest0, GateType::Interrupt);
        interruptDescriptorTable.at(33) = constructInterruptDescriptor(fireInterruptRequest1, GateType::Interrupt);
        interruptDescriptorTable.at(34) = constructInterruptDescriptor(fireInterruptRequest2, GateType::Interrupt);
        interruptDescriptorTable.at(35) = constructInterruptDescriptor(fireInterruptRequest3, GateType::Interrupt);
        interruptDescriptorTable.at(36) = constructInterruptDescriptor(fireInterruptRequest4, GateType::Interrupt);
        interruptDescriptorTable.at(37) = constructInterruptDescriptor(fireInterruptRequest5, GateType::Interrupt);
        interruptDescriptorTable.at(38) = constructInterruptDescriptor(fireInterruptRequest6, GateType::Interrupt);
        interruptDescriptorTable.at(39) = constructInterruptDescriptor(fireInterruptRequest7, GateType::Interrupt);
        interruptDescriptorTable.at(40) = constructInterruptDescriptor(fireInterruptRequest8, GateType::Interrupt);
        interruptDescriptorTable.at(41) = constructInterruptDescriptor(fireInterruptRequest9, GateType::Interrupt);
        interruptDescriptorTable.at(42) = constructInterruptDescriptor(fireInterruptRequest10, GateType::Interrupt);
        interruptDescriptorTable.at(43) = constructInterruptDescriptor(fireInterruptRequest11, GateType::Interrupt);
        interruptDescriptorTable.at(44) = constructInterruptDescriptor(fireInterruptRequest12, GateType::Interrupt);
        interruptDescriptorTable.at(45) = constructInterruptDescriptor(fireInterruptRequest13, GateType::Interrupt);
        interruptDescriptorTable.at(46) = constructInterruptDescriptor(fireInterruptRequest14, GateType::Interrupt);
        interruptDescriptorTable.at(47) = constructInterruptDescriptor(fireInterruptRequest15, GateType::Interrupt);

        //
        idtPointer = {
                (sizeof(InterruptDescriptor) * tableLength) - 1,
                interruptDescriptorTable.data()
        };

        //
        loadIdtTable(&idtPointer);
    }
}