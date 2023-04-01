/* Copyright (C) 2021 David Price - All Rights Reserved
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

#include "interrupt_descriptor.h"
#include <bit>
#include <stdoffset.h>

namespace boot {

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
    auto constructInterruptDescriptor(int (*handler)(), GateType type) -> InterruptDescriptor {
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
