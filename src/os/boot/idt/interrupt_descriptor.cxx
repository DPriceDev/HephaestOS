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

#include <bit>
#include <stdoffset.h>

export module os.boot.interrupts.descriptor;

namespace boot {

    constexpr uint16_t InterruptSegment = 0x08;

    export enum class GateType { Interrupt = 0xE, Trap = 0xF };

    export enum class DescriptorPrivilege { Kernel = 0, UserSpace = 3 };

    export struct [[gnu::packed]] TypeAttributes {
        GateType gateType : 4;
        uint8_t storageSegment : 1;
        DescriptorPrivilege descriptorPrivilege : 2;
        bool isPresent : 1;
    };

    export struct [[gnu::packed]] InterruptDescriptor {
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
    export auto constructInterruptDescriptor(int (*handler)(), GateType type) -> InterruptDescriptor {
        return InterruptDescriptor {
            .lowerOffset = static_cast<uint16_t>(std::bit_cast<uintptr_t>(handler) & std::Mask16Bit),
            .selector = InterruptSegment,
            .zero = 0,
            .gateType = TypeAttributes { .gateType = type,
                                         .storageSegment = 0,
                                         .descriptorPrivilege = DescriptorPrivilege::Kernel,
                                         .isPresent = true },
            .higherOffset =
                static_cast<uint16_t>((std::bit_cast<uintptr_t>(handler) >> std::Offset16Bit) & std::Mask16Bit)
        };
    }
}// namespace boot
