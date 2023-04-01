// Copyright (C) 2022 David Price - All Rights Reserved
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

#ifndef HEPHAEST_OS_BOOT_INFO_H
#define HEPHAEST_OS_BOOT_INFO_H

#include <cstdint>

#include "paging/model/page_directory_entry.h"
#include "paging/model/page_table_entry.h"

namespace boot {

    struct BootInfo {
        PageDirectoryEntry* pageDirectory;
        PageTableEntry* pageTable;
        uintptr_t virtualBase;
        uintptr_t bootStart;
        uintptr_t bootEnd;
    };
}// namespace boot

#endif// HEPHAEST_OS_BOOT_INFO_H
