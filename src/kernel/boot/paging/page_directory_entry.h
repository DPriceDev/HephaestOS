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

//
// Created by david on 06/04/2022.
//

#ifndef HEPHAISTOS_PAGE_DIRECTORY_ENTRY_H
#define HEPHAISTOS_PAGE_DIRECTORY_ENTRY_H

#include <cstdint>

#include "page_table_entry.h"

namespace kernel::boot::paging {

    // Defines the access flags of a given Page Directory Entry.
    struct [[gnu::packed]] PageDirectoryAccess {
        bool isPresent : 1;
        bool canWrite : 1;
        bool hasUserAccess : 1;
        bool writeThrough : 1;
        bool isCacheDisabled : 1;
        bool isAccessed : 1;
        bool isDirty : 1;
        bool isMibSize : 1;
    };

    // Defines a Page Directory Entry with a set of access flags and the top 20 bits of
    // The address this entry points to.
    struct [[gnu::packed]] PageDirectoryEntry {
        PageDirectoryAccess access;
        bool global : 1;
        uint8_t unused : 3;
        uint32_t address : 20;
    };

}

#endif //HEPHAISTOS_PAGE_DIRECTORY_ENTRY_H
