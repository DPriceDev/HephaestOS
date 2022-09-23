// Copyright (C) 2022 David Price - All Rights Reserved
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

#include "paging.h"
#include <cstdint>
#include <array.h>
#include <algorithm.h>
#include <stdoffset.h>

#include "page_directory_entry.h"

namespace kernel::boot::paging {

    // todo: Move to linker script
    // Page directory and first page table arrays.
    std::Array<PageDirectoryEntry, PAGE_DIRECTORY_SIZE> pageDirectory __attribute__((aligned(4096)));
    std::Array<PageTableEntry, PAGE_TABLE_SIZE> firstPageTable __attribute__((aligned(4096)));

    void setFirstTableInDirectory();
    void identityMapFirstTable();
    void zeroPageDirectory();

    // Sets up paging by clearing the page directory and identity maps the first page table,
    // before loading the page directory and enabling paging.
    // todo pass through directory and table pointers
    void setupPaging() {
        zeroPageDirectory();
        // todo higher half map, pass in kernel pointer
        identityMapFirstTable();
        // todo assign specific table
        setFirstTableInDirectory();

        // enable paging
        loadPageDirectory(pageDirectory.data());
        enablePaging();
    }

    // Initialize all page table entries to empty entries.
    void zeroPageDirectory() {
        for (auto & element : pageDirectory) {
            element = PageDirectoryEntry {
                .access = PageDirectoryAccess {
                    .canWrite = true
                },
            };
        };
    }

    // Setup each entry of the first page table to map identically to the physical address.
    void identityMapFirstTable() {
        uint32_t address = 0;
        for (auto & entry : firstPageTable) {
            entry = PageTableEntry {
                .access = PageTableAccess {
                    .isPresent = true
                },
                .address = (address >> Offset12Bit) & Mask20Bit
            };
            address += PAGE_SIZE;
        };
    }

    // Assign the first page table to the first entry in the page directory.
    void setFirstTableInDirectory() {
        auto adr = reinterpret_cast<unsigned int>(firstPageTable.data());
        pageDirectory.front() = {
                .access = PageDirectoryAccess {
                        .isPresent = true,
                        .canWrite = true
                },
                .address = (adr >> Offset12Bit) & Mask20Bit
        };
    }

}