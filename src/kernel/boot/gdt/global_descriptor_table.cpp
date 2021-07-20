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

#include "global_descriptor_table.h"

namespace kernel::boot::gdt {

    // todo c++ bit shifting?
    constexpr GlobalDescriptor constructGlobalDescriptor(
            const uint32_t baseAddress,
            const uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    ) {
        return GlobalDescriptor {
                static_cast<uint16_t>((memoryLimit & 0xFFFF)),
                static_cast<uint16_t>((baseAddress & 0xFFFFFF)),
                access,
                static_cast<uint8_t>((memoryLimit & 0xF0000) >> 16U),
                true,
                false,
                flags.size,
                flags.granularity,
                static_cast<uint8_t>((baseAddress & 0xF000000) >> 24U)
        };
    }

    constexpr GlobalDescriptor globalDescriptorTable[5] = {
            constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
            constructGlobalDescriptor(0, 0xFFFFF, codeKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, 0xFFFFF, dataKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, 0xFFFFF, codeUserAccess, gran32Flags),
            constructGlobalDescriptor(0, 0xFFFFF, dataUserAccess, gran32Flags)
    };

    constexpr GdtPointer gdtPointer {
            sizeof(globalDescriptorTable) - 1,
            globalDescriptorTable
    };

    void initializeGlobalDescriptorTable() {
        loadGdtTable(&gdtPointer);
    }
}