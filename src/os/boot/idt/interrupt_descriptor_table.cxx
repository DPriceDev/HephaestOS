/* Copyright (C) 2023 David Price - All Rights Reserved
 * This file is part of HephaestOS.
 *
 * HephaestOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaestOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
 */

module;

#include "array.h"

import os.boot.interrupts.descriptor;

export module os.boot.interrupts.table;

namespace boot {

     /**
     *
     */
    struct [[gnu::packed]] IdtPointer {
        uint16_t size;
        const InterruptDescriptor* pointer;
    };

    //
    constexpr uint32_t IDT_TABLE_LENGTH = 256;

    /**
     *
     * @param pointer
     */
    extern "C" void loadIdtTable(const IdtPointer* pointer);

    /**
     *
     */
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

    /**
     *
     */
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
    export void initializeInterruptDescriptorTable() { loadIdtTable(&idtPointer); }
}// namespace boot