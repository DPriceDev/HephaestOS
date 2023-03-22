// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaistOS.
//
// HephaistOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaistOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAISTOS_BOOTALLOCATOR_H
#define HEPHAISTOS_BOOTALLOCATOR_H

#include "paging/paging.h"
#include "cstddef"
#include <cstdint>

namespace boot {

    class BootAllocator {
        std::uintptr_t currentAddress;
        std::uintptr_t virtualAddress;
        PageTableEntry* pageTable;

      public:
        BootAllocator(
            std::uintptr_t baseVirtualAddress,
            std::uintptr_t physicalAddress,
            PageTableEntry* kernelPageTable
        );

        auto allocate(std::size_t count, std::size_t alignment = 1) -> std::byte*;
    };
}// namespace boot

#endif// HEPHAISTOS_BOOTALLOCATOR_H
