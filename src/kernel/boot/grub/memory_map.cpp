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

#include "memory_map.h"
#include <span.h>
#include <format.h>

namespace kernel::boot::grub {

    auto constructMemoryMap(const MultiBootInfo * multiBootInfo) -> void {

        if (multiBootInfo->flags.isMemoryAvailable) {
            auto size = multiBootInfo->memoryMapLength;
            auto memSize = sizeof(MemoryMapEntry);
            auto entryCount = size / memSize;

            auto memoryMap = std::Span(multiBootInfo->memoryMapPtr, entryCount);

            std::print("\nMemory Map!\n");

            std::print(
                "\nlower size: {}KB upper size: {}KB\n\n",
                multiBootInfo->lowerMemorySize,
                multiBootInfo->upperMemorySize
            );

            for (const MemoryMapEntry & memoryMapEntry : memoryMap) {
                std::print("**Memory Map Entry**\n");
                std::print("Type: {}\n", memoryMapEntry.type);
                std::print("Size: {}\n", memoryMapEntry.size);
                long long address = memoryMapEntry.addr_low + memoryMapEntry.addr_high;
                std::print("Start Address: {}\n", address);
                long long length = memoryMapEntry.len_low + memoryMapEntry.len_high;
                std::print("Length: {}\n\n", length);
            }

            std::print("\n");

            // organize memory locations into groups

            // build memory map and return?
        }
    }
}