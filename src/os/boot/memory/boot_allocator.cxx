// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

module;

#include <bit>
#include <cstddef>
#include <cstdint>

import os.boot.paging;
export import os.boot.paging.table;
import os.boot.paging.directory;

export module os.boot.memory.boot_allocator;

export namespace boot {

    class BootAllocator {
        std::uintptr_t currentAddress;
        std::uintptr_t virtualAddress;
        PageTableEntry* pageTable;

      public:
        BootAllocator(
            std::uintptr_t virtualBaseAddress,
            std::uintptr_t physicalAddress,
            PageTableEntry* kernelPageTable
        )   : currentAddress(physicalAddress), virtualAddress(virtualBaseAddress), pageTable(kernelPageTable) {}

        auto allocate(std::size_t count, std::size_t alignment = 1) -> std::byte* {
            const auto startAddress = (currentAddress / alignment) + (currentAddress % alignment ? alignment : 0);
            const auto endAddress = startAddress + count;

            mapAddressRangeInTable(pageTable, virtualAddress + currentAddress, currentAddress, endAddress);

            currentAddress = endAddress;
            return std::bit_cast<std::byte*>(virtualAddress + startAddress);
        }

        [[nodiscard]] auto nextAvailableMemory() const -> uintptr_t { return currentAddress; }
    };
}// namespace boot
