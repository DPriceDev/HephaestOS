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

#ifndef HEPHAIST_OS_KERNEL_BOOT_PAGING_PAGE_TABLE_ENTRY_H
#define HEPHAIST_OS_KERNEL_BOOT_PAGING_PAGE_TABLE_ENTRY_H

#include <cstdint>

namespace kernel::boot::paging {

    // Defines the access flags of a given Page Table Entry.
    struct [[gnu::packed]] PageTableAccess {
        bool isPresent: 1 = false;
        bool canWrite: 1 = false;
        bool hasUserAccess: 1 = false;
        bool writeThrough: 1 = false;
        bool isCacheDisabled: 1 = false;
        bool isAccessed: 1 = false;
        bool isDirty: 1 = false;
        bool pageAttributeTable: 1 = false;
    };

    // Defines a Page Table Entry with a set of access flags and the top 20 bits of
    // The address this entry points to.
    struct [[gnu::packed]] PageTableEntry {
        PageTableAccess access = PageTableAccess();
        bool global: 1 = false;
        uint8_t unused: 3 = 0;
        uint32_t address: 20 = 0x0;
    };
}

#endif // HEPHAIST_OS_KERNEL_BOOT_PAGING_PAGE_TABLE_ENTRY_H
