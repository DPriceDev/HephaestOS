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
#include <algorithm.h>

namespace kernel::boot::grub {

    auto constructMemoryMap(const MultiBootInfo * multiBootInfo) -> void {

        if(multiBootInfo->flags.isMemoryAvailable) {
            auto size = multiBootInfo->memoryMapLength;
            auto memSize = sizeof(MemoryMapEntry);
            auto div = size / memSize;

            auto memoryMap = std::Span(multiBootInfo->memoryMapPtr, div);

            auto* start = memoryMap.begin();
            auto* end = memoryMap.end();

            // todo: implement an array? or a vector to capture these values?

            std::forEach(start, end, [] (const auto & memoryMapEntry) -> void {
                auto test = memoryMapEntry.type;
                auto useTest = test;
            });

//            auto memoryMap = lib::Span(multiBootInfo->memoryMapPtr, multiBootInfo->memoryMapLength);
//
//            auto bas = memoryMap.begin();
//            //auto* b = *bas;
//
//            lib::forEach(memoryMap.begin(), memoryMap.end(), [] (const auto & memoryMapEntry) -> void {
//                auto test = memoryMapEntry.type;
//            });
        }
    }

}