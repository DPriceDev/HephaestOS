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

#include <bit>
#include "boot_elf_loader.h"
#include <result.h>
#include <span.h>
#include <string.h>

namespace kernel::boot::elf {

    auto extractProgramHeaders(const ElfHeader* header, uintptr_t headerAddress) -> std::Span<const ProgramHeader>;

    auto getElfInfo(uintptr_t headerAddress) -> std::Result<ElfInfo> {
        const auto* elfHeader = std::bit_cast<ElfHeader*>(headerAddress);

        const auto& identifier = elfHeader->identifier;
        const auto isElf = identifier[0] == 'E' && identifier[1] == 'L' && identifier[2] == 'F';
        if (!isElf) {
            return std::Result<ElfInfo>::failure();
        }

        return std::Result<ElfInfo>::success(
            {
                .entryAddress = elfHeader->programEntryAddress,
                .header = elfHeader,
                .programHeaders = extractProgramHeaders(elfHeader, headerAddress)
            }
        );
    }

    auto extractProgramHeaders(const ElfHeader* header, uintptr_t headerAddress) -> std::Span<const ProgramHeader> {
        const auto* programHeader = std::bit_cast<ProgramHeader*>(headerAddress + header->programHeaderOffset);
        return { programHeader, header->programHeaderCount };
    }

    void loadStaticElf(const ElfInfo& info) {
        for (const auto& programHeader : info.programHeaders) {
            const auto addr = std::bit_cast<uintptr_t>(info.header);
            const auto dsf = addr + programHeader.dataOffset;
            const auto* programAddress = std::bit_cast<void*>(dsf);
            auto* memoryAddress = std::bit_cast<void*>(programHeader.virtualAddress);
            memset(memoryAddress, 0, programHeader.memorySize);
            memcpy(memoryAddress, programAddress, programHeader.fileSize);
        }
    }

    void loadRelocatableElf(const ElfInfo& info, uintptr_t loadAddress) {

    }

}
