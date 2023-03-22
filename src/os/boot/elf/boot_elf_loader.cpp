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
#include <string.h>

namespace kernel::boot::elf {

    auto getExecutableElfInfo(const Elf32_Ehdr* header, uintptr_t headerAddress) -> ElfInfo;

    auto extractExecutableElf(const Elf32_Ehdr* header, uintptr_t headerAddress) -> StaticExecutableElf;

    auto extractDynamicExecutableElf(const Elf32_Ehdr* header, uintptr_t headerAddress) -> DynamicExecutableElf;

    auto extractProgramHeaders(const Elf32_Ehdr* header, uintptr_t headerAddress) -> std::Span<const Elf32_Phdr>;

    auto getElfInfo(uintptr_t headerAddress) -> std::Result<ElfInfo> {
        const auto* elfHeader = std::bit_cast<Elf32_Ehdr*>(headerAddress);

        const auto& identifier = elfHeader->e_ident;
        const auto isElf = identifier[1] == 'E' && identifier[2] == 'L' && identifier[3] == 'F';
        if (!isElf) {
            return std::Result<ElfInfo>::failure();
        }

        if (elfHeader->e_type != ET_EXEC) {
            return std::Result<ElfInfo>::failure();
        }

        return std::Result<ElfInfo>::success(getExecutableElfInfo(elfHeader, headerAddress));
    }

    auto getExecutableElfInfo(const Elf32_Ehdr* header, uintptr_t headerAddress) -> ElfInfo {
        if (header->e_entry == 0) {
            return ElfInfo { extractDynamicExecutableElf(header, headerAddress) };
        }

        return ElfInfo { extractExecutableElf(header, headerAddress) };
    }

    std::size_t getProgramSize(const std::Span<const Elf32_Phdr> headers) {
        std::size_t memorySize = 0;
        for (const auto& header: headers) {
            memorySize += header.p_memsz;
        }
        return memorySize;
    }

    auto extractExecutableElf(const Elf32_Ehdr* header, uintptr_t headerAddress) -> StaticExecutableElf {
        const auto programHeaders = extractProgramHeaders(header, headerAddress);
        const auto memorySize = getProgramSize(programHeaders);
        return StaticExecutableElf {
            .entryAddress = header->e_entry,
            .headerAddress = headerAddress,
            .memorySize = memorySize,
            .programHeaders = programHeaders
        };
    }

    auto extractDynamicExecutableElf(const Elf32_Ehdr* header, uintptr_t headerAddress) -> DynamicExecutableElf {
        const auto programHeaders = extractProgramHeaders(header, headerAddress);
        const auto memorySize = getProgramSize(programHeaders);
        return DynamicExecutableElf {
            .headerAddress = headerAddress,
            .memorySize = memorySize,
            .programHeaders = programHeaders
        };
    }

    auto extractProgramHeaders(const Elf32_Ehdr* header, uintptr_t headerAddress) -> std::Span<const Elf32_Phdr> {
        const auto* programHeader = std::bit_cast<Elf32_Phdr*>(headerAddress + header->e_phoff);
        return { programHeader, header->e_phnum };
    }

    void loadExecutableElf(
        uintptr_t headerAddress,
        std::Span<const Elf32_Phdr> programHeaders,
        uintptr_t loadAddress
    ) {
        for (const auto& programHeader: programHeaders) {
            const auto* programAddress = std::bit_cast<void*>(headerAddress + programHeader.p_offset);
            auto* memoryAddress = std::bit_cast<void*>(loadAddress);
            memset(memoryAddress, 0, programHeader.p_memsz + programHeader.p_vaddr);
            memcpy(memoryAddress, programAddress, programHeader.p_filesz);
        }
    }

    void loadElf(const StaticExecutableElf& elf) {
        loadExecutableElf(elf.headerAddress, elf.programHeaders, elf.entryAddress);
    }

    void loadElf(const DynamicExecutableElf& elf, uintptr_t loadAddress) {
        loadExecutableElf(elf.headerAddress, elf.programHeaders, loadAddress);
    }
}
