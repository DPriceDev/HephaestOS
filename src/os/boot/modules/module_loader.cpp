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
        -> std::Result<uintptr_t> {
        std::print("INFO: Loading {} Boot Module{}\n", bootModules.size(), (bootModules.size()) ? "" : "s");

        if (bootModules.empty()) {
            std::print("ERROR: No Boot Modules Found\n");
            return std::Result<uintptr_t>::failure();
        }

        uintptr_t kernelAddress = 0;// todo: Make optional?
        for (const auto& bootModule : bootModules) {

            mapAddressRangeInTable(
                bootInfo.bootPageTable,
                bootInfo.baseVirtualAddress + bootModule.moduleStart,
                bootModule.moduleStart,
                bootModule.moduleEnd
            );

            const auto loadedModule = loadBootModule(bootModule, allocator, bootInfo);
            if (loadedModule.isValid() && loadedModule.get().name == "kernel") {
                kernelAddress = loadedModule.get().address;
            }
        }

        if (kernelAddress == 0) {
            return std::Result<uintptr_t>::failure();
        }

        return std::Result<uintptr_t>::success(kernelAddress);
    }

    auto loadBootModule(const ModuleEntry& bootModule, BootAllocator& allocator, const BootInfo& bootInfo)
        -> std::Result<LoadedModule> {
        const auto moduleName = std::StringView { std::bit_cast<char*>(bootInfo.baseVirtualAddress + bootModule.string) };
        std::print("INFO: Loading Boot Module: {}\n", moduleName);

        const auto elfAddress = bootInfo.baseVirtualAddress + bootModule.moduleStart;
        const auto elfInfoResult = getElfInfo(elfAddress);

        if (elfInfoResult.isNotValid()) {
            std::print("ERROR: Failed to load boot module: {}\n", moduleName);
            return std::Result<LoadedModule>::failure();
        }

        ElfInfo elfInfo = elfInfoResult.get();

        const auto elfVisitor = [&allocator, &bootInfo](const auto& elf) { return loadElf(elf.get(), allocator, bootInfo); };

        const auto entryAddress = std::visit(elfVisitor, elfInfo);
        return std::Result<LoadedModule>::success({ moduleName, entryAddress });
    }

    auto loadElf(const StaticExecutableElf& elf, const BootAllocator&, const BootInfo& bootInfo) -> uintptr_t {
        const auto physicalStart = elf.entryAddress - bootInfo.baseVirtualAddress;
        const auto physicalEnd = physicalStart + elf.memorySize;
        mapAddressRangeInTable(
            bootInfo.bootPageTable,
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