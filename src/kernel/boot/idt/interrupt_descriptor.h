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

#include <stdint.h>

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

    /**
     * Constructs an Interrupt Descriptor that can be inserted in a Interrupt descriptor table.
     * This takes a handler that is called when the interrupt associated with this descriptor is
     * fired.
     * The x86 implementation of the Interrupt Descriptor splits the offset structure; therefore
     * the lower and upper sections of the offset are bit-masked and bit-shifted into place.
     *
     * @param handler is a pointer to a method that will be called if the interrupt fires.
     * @param type defines the interrupt gate to used, Interrupt for interrupts, Trap and Interrupt
     * for exceptions.
     * @return an interrupt descriptor setup to call the provided method on the interrupt firing.
     */
    auto constructInterruptDescriptor(int (*handler)(), GateType type) -> InterruptDescriptor;
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_DESCRIPTOR_H
