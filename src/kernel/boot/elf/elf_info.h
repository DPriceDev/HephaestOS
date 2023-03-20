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

#ifndef HEPHAISTOS_ELF_INFO_H
#define HEPHAISTOS_ELF_INFO_H

#include <cstdint>
#include <span.h>
#include "elf_header.h"
#include <variant_base.h>

namespace kernel::boot::elf {

    struct ExecutableElf {
        std::uintptr_t entryAddress;
        std::uintptr_t headerAddress;
        std::Span<const ProgramHeader> programHeaders;
    };

    struct RelocatableElf {
        std::uintptr_t headerAddress;
        std::Span<const ProgramHeader> programHeaders;
    };

    using ElfInfo = std::Variant<ExecutableElf, RelocatableElf>;
}

#endif // HEPHAISTOS_ELF_INFO_H
