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

#include "paging.h"
#include "model/paging_constants.h"
#include <algorithm.h>
#include <bit>
#include <cstdint>
#include <stdoffset.h>

#include "model/page_directory_entry.h"
#include "span.h"

namespace boot {

    struct EntryAddressMask {
        uint16_t : 12;
        uint32_t top : 20;
    };

    // Initialize all page table entries to empty entries.
    void zeroPageDirectory(std::Span<PageDirectoryEntry>& pageDirectory) {
        std::forEach(pageDirectory.begin(), pageDirectory.end(), [](auto& element) {
            element = PageDirectoryEntry {
                .access = PageDirectoryAccess { .canWrite = true },
            };
        });
    }

    // Setup each entry of the first page table to map identically to the physical address.
    void mapAddressRangeInTable(
        PageTableEntry* pageTablePointer,
        uintptr_t virtualStartAddress,
        uintptr_t startAddress,
        uintptr_t endAddress
    ) {
        auto pageTable = std::Span(pageTablePointer, PAGE_TABLE_SIZE);

        uintptr_t address = startAddress;
        uint32_t startIndex = (virtualStartAddress & 0xFFFFFFF) / PAGE_SIZE;
        uint32_t endIndex = startIndex + ((endAddress / PAGE_SIZE) - (startAddress / PAGE_SIZE));

        std::forEach(pageTable.begin() + startIndex, pageTable.begin() + endIndex + 1, [&address](auto& entry) {
            entry = PageTableEntry { .access = PageTableAccess { .isPresent = true },
                                     .address = std::bit_cast<EntryAddressMask>(address).top };
            address += PAGE_SIZE;
        });
    }

    // Assign the first page table to the first entry in the page directory.
    void updateTableInDirectory(
        std::Span<PageDirectoryEntry>& directory,
        uintptr_t virtualAddress,
        PageTableEntry* table
    ) {
        auto address = std::bit_cast<uintptr_t>(table);
        auto index = (virtualAddress >> std::Offset22Bit) & std::Mask10Bit;
        directory[index] = { .access = PageDirectoryAccess { .isPresent = true, .canWrite = true },
                             .address = std::bit_cast<EntryAddressMask>(address).top };
    }

    void setupIdentityPage(
        PageDirectoryEntry* pageDirectoryPointer,
        uintptr_t kernelStartAddress,
        uintptr_t kernelEndAddress
    ) {
        auto pageDirectory = std::Span(pageDirectoryPointer, PAGE_DIRECTORY_SIZE);
        [[gnu::aligned(4096)]] PageTableEntry identityMappedPageTableArray[PAGE_TABLE_SIZE];
        auto identityMappedPageTable = std::Span(identityMappedPageTableArray, PAGE_TABLE_SIZE);

        mapAddressRangeInTable(
            identityMappedPageTable.data(), kernelStartAddress, kernelStartAddress, kernelEndAddress
        );

        updateTableInDirectory(pageDirectory, 0, identityMappedPageTable.data());
    }

    void setupHigherHalfPage(
        PageDirectoryEntry* pageDirectoryPointer,
        PageTableEntry* kernelPageTablePointer,
        uintptr_t virtualKernelBaseAddress,
        uintptr_t kernelStartAddress,
        uintptr_t kernelEndAddress
    ) {
        auto pageDirectory = std::Span(pageDirectoryPointer, PAGE_DIRECTORY_SIZE);
        auto higherHalfKernelPageTable = std::Span(kernelPageTablePointer, PAGE_TABLE_SIZE);

        mapAddressRangeInTable(
            higherHalfKernelPageTable.data(),
            virtualKernelBaseAddress + kernelStartAddress,
            kernelStartAddress,
            kernelEndAddress
        );

        updateTableInDirectory(pageDirectory, virtualKernelBaseAddress, higherHalfKernelPageTable.data());
    }

    void initializePaging(
        MultiBootInfo*,
        PageDirectoryEntry* pageDirectoryPointer,
        PageTableEntry* kernelPageTablePointer,
        uintptr_t virtualKernelBaseAddress,
        uintptr_t kernelStartAddress,
        uintptr_t kernelEndAddress
    ) {
        auto pageDirectory = std::Span(pageDirectoryPointer, PAGE_DIRECTORY_SIZE);

        zeroPageDirectory(pageDirectory);

        setupIdentityPage(pageDirectoryPointer, kernelStartAddress, kernelEndAddress);

        setupHigherHalfPage(
            pageDirectoryPointer, kernelPageTablePointer, virtualKernelBaseAddress, kernelStartAddress, kernelEndAddress
        );

        // enable paging
        loadPageDirectory(pageDirectory.data());
        enablePaging();
    }

    void unmapPageTable(std::Span<PageDirectoryEntry, std::dynamicExtent>, int) {}

    void unmapLowerKernel(PageDirectoryEntry* pageDirectoryPointer) {
        auto pageDirectory = std::Span(pageDirectoryPointer, PAGE_DIRECTORY_SIZE);
        pageDirectory.front() = PageDirectoryEntry {
            .access = PageDirectoryAccess { .canWrite = true },
        };
    }
}// namespace boot