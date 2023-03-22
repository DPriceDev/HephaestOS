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
#include "array.h"

namespace boot {

    // Array of Interrupt Descriptors that defines the Interrupt Descriptor Table.
    static const std::Array<InterruptDescriptor, IDT_TABLE_LENGTH> interruptDescriptorTable {
        // Exceptions
        constructInterruptDescriptor(fireException0, GateType::Trap),
        constructInterruptDescriptor(fireException1, GateType::Trap),
        constructInterruptDescriptor(fireException2, GateType::Trap),
        constructInterruptDescriptor(fireException3, GateType::Trap),
        constructInterruptDescriptor(fireException4, GateType::Trap),
        constructInterruptDescriptor(fireException5, GateType::Trap),
        constructInterruptDescriptor(fireException6, GateType::Trap),
        constructInterruptDescriptor(fireException7, GateType::Trap),
        constructInterruptDescriptor(fireException8, GateType::Trap),
        constructInterruptDescriptor(fireException9, GateType::Trap),
        constructInterruptDescriptor(fireException10, GateType::Trap),
        constructInterruptDescriptor(fireException11, GateType::Trap),
        constructInterruptDescriptor(fireException12, GateType::Trap),
        constructInterruptDescriptor(fireException13, GateType::Trap),
        constructInterruptDescriptor(fireException14, GateType::Trap),
        constructInterruptDescriptor(fireException15, GateType::Trap),
        constructInterruptDescriptor(fireException16, GateType::Trap),
        constructInterruptDescriptor(fireException17, GateType::Trap),
        constructInterruptDescriptor(fireException18, GateType::Trap),
        constructInterruptDescriptor(fireException19, GateType::Trap),
        constructInterruptDescriptor(fireException20, GateType::Trap),
        constructInterruptDescriptor(fireException21, GateType::Trap),
        constructInterruptDescriptor(fireException22, GateType::Trap),
        constructInterruptDescriptor(fireException23, GateType::Trap),
        constructInterruptDescriptor(fireException24, GateType::Trap),
        constructInterruptDescriptor(fireException25, GateType::Trap),
        constructInterruptDescriptor(fireException26, GateType::Trap),
        constructInterruptDescriptor(fireException27, GateType::Trap),
        constructInterruptDescriptor(fireException28, GateType::Trap),
        constructInterruptDescriptor(fireException29, GateType::Trap),
        constructInterruptDescriptor(fireException30, GateType::Trap),
        constructInterruptDescriptor(fireException31, GateType::Trap),
        // Interrupts
        constructInterruptDescriptor(fireInterruptRequest0, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest1, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest2, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest3, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest4, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest5, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest6, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest7, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest8, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest9, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest10, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest11, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest12, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest13, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest14, GateType::Interrupt),
        constructInterruptDescriptor(fireInterruptRequest15, GateType::Interrupt)
    };

    // Structure holding the Interrupt descriptor Table array pointer and size of the array.
    static const IdtPointer idtPointer { (sizeof(InterruptDescriptor) * IDT_TABLE_LENGTH) - 1,
                                         interruptDescriptorTable.data() };

    /**
     *
     */
    void initializeInterruptDescriptorTable() { loadIdtTable(&idtPointer); }
}// namespace boot