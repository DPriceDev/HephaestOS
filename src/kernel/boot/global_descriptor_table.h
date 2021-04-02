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

#ifndef HEPHAISTOS_GLOBAL_DESCRIPTOR_TABLE_H
#define HEPHAISTOS_GLOBAL_DESCRIPTOR_TABLE_H

#include "kernel/types.h"

namespace kernel {

    extern "C" void setGlobalDescriptorTable(const uint64_t tablePointer[], uint16_t tableSize);

    //constexpr

    static constexpr uint64_t constructGlobalDescriptor(int32_t baseAddress, int32_t memoryLimit, int16_t flags) {
        uint64_t descriptor = memoryLimit & 0x000F0000;         // set bits 19:16 of the limit to 19:16 in descriptor.
        descriptor |= (flags << 8) & 0x00F0FF00;                // set type, p, dpl, s, g, d/b, l and avl fields
        descriptor |= (baseAddress >> 16) & 0x000000FF;         // set base bits 23:16
        descriptor |= baseAddress & 0xFF000000;                 // set base bits 31:24

        // Shift by 32 to allow for low part of segment
        descriptor <<= 32;

        // Create the low 32 bit segment
        descriptor |= baseAddress << 16;                        // set base bits 15:0
        descriptor |= memoryLimit & 0x0000FFFF;                 // set limit bits 15:0

        return descriptor;
    }

    static constexpr uint64_t globalDescriptorTable[] = {
            constructGlobalDescriptor(0, 0, 0),
            constructGlobalDescriptor(0, 0x000FFFFF, 0),
            constructGlobalDescriptor(0, 0x000FFFFF, 0)
    };
}

#endif //HEPHAISTOS_GLOBAL_DESCRIPTOR_TABLE_H
