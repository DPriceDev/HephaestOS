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

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_H

namespace kernel::boot::idt {

    constexpr uint16_t InterruptSegment = 0x08;

    enum class GateType {
        Interrupt = 0xE,
        Trap = 0xF
    };

    enum class DescriptorPrivilege {
        Kernel = 0,
        UserSpace = 3
    };

    struct [[gnu::packed]] TypeAttributes {
        GateType gateType: 4;
        uint8_t storageSegment: 1;
        DescriptorPrivilege descriptorPrivilege: 2;
        bool isPresent: 1;
    };

    struct [[gnu::packed]] InterruptDescriptor {
        uint16_t lowerOffset;
        uint16_t selector;
        uint8_t zero;
        TypeAttributes gateType;
        uint16_t higherOffset;
    };
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_H
