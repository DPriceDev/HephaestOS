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

#include "module_loader.h"
#include <bit>
#include <elf/elf.h>
#include <format.h>

namespace boot {
    auto loadModules(const std::Span<ModuleEntry>& bootModules, BootAllocator& allocator, const BootInfo& bootInfo)
        -> std::Optional<uintptr_t> {
        std::print("INFO: Loading {} Boot Module{}\n", bootModules.size(), (bootModules.size()) ? "" : "s");

        if (bootModules.empty()) {
            std::print("ERROR: No Boot Modules Found\n");
            return std::nullOptional;
        }

        uintptr_t kernelAddress = 0;// todo: Make optional?
        for (const auto& bootModule : bootModules) {

            mapAddressRangeInTable(
                bootInfo.pageTable,
                bootInfo.virtualBase + bootModule.moduleStart,
                bootModule.moduleStart,
                bootModule.moduleEnd
            );

            const auto loadedModule = loadBootModule(bootModule, allocator, bootInfo);
            if (loadedModule && loadedModule->name == "kernel") {
                kernelAddress = loadedModule->address;
            }
        }

        if (kernelAddress == 0) {
            return std::nullOptional;
        }

        return std::Optional<uintptr_t>(kernelAddress);
    }

    auto loadBootModule(const ModuleEntry& bootModule, BootAllocator& allocator, const BootInfo& bootInfo)
        -> std::Optional<LoadedModule> {
        const auto moduleName = std::StringView { std::bit_cast<char*>(bootInfo.virtualBase + bootModule.string) };
        std::print("INFO: Loading Boot Module: {}\n", moduleName);

        const auto elfAddress = bootInfo.virtualBase + bootModule.moduleStart;
        const auto elfInfoResult = getElfInfo(elfAddress);

        if (!elfInfoResult) {
            std::print("ERROR: Failed to load boot module: {}\n", moduleName);
            return std::nullOptional;
        }

        ElfInfo elfInfo = elfInfoResult.value();

        const auto elfVisitor = [&allocator, &bootInfo](const auto& elf) { return loadElf(elf.value(), allocator, bootInfo); };

        const auto entryAddress = std::visit(elfVisitor, elfInfo);
        return std::Optional<LoadedModule>({ moduleName, entryAddress });
    }

    auto loadElf(const StaticExecutableElf& elf, const BootAllocator&, const BootInfo& bootInfo) -> uintptr_t {
        const auto physicalStart = elf.entryAddress - bootInfo.virtualBase;
        const auto physicalEnd = physicalStart + elf.memorySize;
        mapAddressRangeInTable(
            bootInfo.pageTable,
            elf.entryAddress,
            physicalStart,
            physicalEnd
        );
        enablePaging();
        loadElf(elf);
        return elf.entryAddress;
    }

    auto loadElf(const DynamicExecutableElf& elf, BootAllocator& allocator, const BootInfo&) -> uintptr_t {
        const auto address = std::bit_cast<uintptr_t>(allocator.allocate(elf.memorySize));
        loadElf(elf, address);
        return address;
    }
}// namespace boot