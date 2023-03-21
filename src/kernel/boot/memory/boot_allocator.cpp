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

#include <bit>
#include "boot_allocator.h"

namespace kernel::boot {

    BootAllocator::BootAllocator(
        std::uintptr_t virtualBaseAddress,
        std::uintptr_t physicalAddress,
        paging::PageTableEntry* kernelPageTable
    ) : currentAddress(physicalAddress),
    virtualBaseAddress(virtualBaseAddress),
    kernelPageTable(kernelPageTable) { }

    auto BootAllocator::allocate(std::size_t count, std::size_t alignment) -> void* {
        const auto startAddress = (currentAddress / alignment) + (currentAddress % alignment ? alignment : 0);
        const auto endAddress = startAddress + count;

        paging::mapAddressRangeInTable(
            kernelPageTable,
            virtualBaseAddress + currentAddress,
            currentAddress,
            endAddress
        );

        currentAddress = endAddress;
        return std::bit_cast<void*>(virtualBaseAddress + startAddress);
    }
}

