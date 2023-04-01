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

#ifndef HEPHAEST_OS_BOOT_ELF_LOADER_H
#define HEPHAEST_OS_BOOT_ELF_LOADER_H

#include <cstdint>
#include <elf/elf.h>
#include <optional.h>
#include <span.h>
#include <variant_base.h>

namespace boot {

    struct StaticExecutableElf {
        std::uintptr_t entryAddress;
        std::uintptr_t headerAddress;
        size_t memorySize;
        std::Span<const ProgramHeader> programHeaders;
    };

    struct DynamicExecutableElf {
        std::uintptr_t headerAddress;
        size_t memorySize;
        std::Span<const ProgramHeader> programHeaders;
    };

    using ElfInfo = std::Variant<StaticExecutableElf, DynamicExecutableElf>;

    // get elf info
    auto getElfInfo(uintptr_t headerAddress) -> std::Optional<ElfInfo>;

    // load static elf to memory
    void loadElf(const StaticExecutableElf& elf);

    void loadElf(const DynamicExecutableElf& elf, uintptr_t loadAddress);
}// namespace boot

#endif// HEPHAEST_OS_BOOT_ELF_LOADER_H
