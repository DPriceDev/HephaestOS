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

#include <span.h>
#include "elf_loader.h"
#include "elf_header.h"
#include "algorithm.h"

namespace kernel::boot::elf {

    void loadModules(ModuleEntry* moduleEntry, std::size_t count) {
        auto moduleEntries = std::Span(moduleEntry, count);

        for (const ModuleEntry & entry : moduleEntries) {
            auto* elfHeader = reinterpret_cast<ElfHeader*>(entry.moduleStart);

            auto* programHeaderTable = reinterpret_cast<ProgramHeader*>(entry.moduleStart + elfHeader->programHeader);

            auto test = 2;
        };
    }


}
