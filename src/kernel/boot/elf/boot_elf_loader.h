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

#ifndef HEPHAISTOS_BOOT_ELF_LOADER_H
#define HEPHAISTOS_BOOT_ELF_LOADER_H

#include <cstdint>
#include "elf.h"
#include "elf_info.h"
#include <variant_base.h>

namespace kernel::boot::elf {

    // get elf info
    auto getElfInfo(uintptr_t headerAddress) -> std::Result<ElfInfo>;

    // load static elf to memory
    void loadElf(const StaticExecutableElf& elf);

    void loadElf(const DynamicExecutableElf& elf, uintptr_t loadAddress);
}

#endif // HEPHAISTOS_BOOT_ELF_LOADER_H
