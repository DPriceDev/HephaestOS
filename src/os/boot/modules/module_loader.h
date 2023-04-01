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

#ifndef HEPHAISTOS_MODULE_LOADER_H
#define HEPHAISTOS_MODULE_LOADER_H

#include "boot_info.h"
#include "grub/multiboot_info.h"
#include "memory/boot_allocator.h"
#include <elf/boot_elf_loader.h>
#include <string_view.h>

namespace boot {
    struct LoadedModule {
        std::StringView name;
        uintptr_t address;
    };

    auto loadModules(const std::Span<ModuleEntry>& bootModules, BootAllocator& allocator, const BootInfo& bootInfo)
        -> std::Optional<uintptr_t>;

    auto loadBootModule(const ModuleEntry& bootModule, BootAllocator& allocator, const BootInfo& bootInfo)
        -> std::Optional<LoadedModule>;

    auto loadElf(const StaticExecutableElf& elf, const BootAllocator& bootAllocator, const BootInfo& bootInfo)
        -> uintptr_t;

    auto loadElf(const DynamicExecutableElf& elf, BootAllocator& bootAllocator, const BootInfo& bootInfo) -> uintptr_t;
}// namespace boot

#endif// HEPHAISTOS_MODULE_LOADER_H
