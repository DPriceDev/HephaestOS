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

module;

#include <bit>
#include <cstdint>
#include <expected.h>
#include <optional.h>
#include <span.h>
#include <string.h>
#include <variant_base.h>

export import os.boot.elf;

export module os.boot.elf.loader;

namespace boot {

    export struct StaticExecutableElf {
        std::uintptr_t entryAddress;
        std::uintptr_t headerAddress;
        size_t memorySize;
        std::Span<const ProgramHeader> programHeaders;
    };

    export struct DynamicExecutableElf {
        std::uintptr_t headerAddress;
        size_t memorySize;
        std::Span<const ProgramHeader> programHeaders;
    };

    export using ElfInfo = std::Variant<StaticExecutableElf, DynamicExecutableElf>;

    auto getExecutableElfInfo(const ElfHeader* header, uintptr_t headerAddress) -> ElfInfo;

    auto extractExecutableElf(const ElfHeader* header, uintptr_t headerAddress) -> StaticExecutableElf;

    auto extractDynamicExecutableElf(const ElfHeader* header, uintptr_t headerAddress) -> DynamicExecutableElf;

    auto extractProgramHeaders(const ElfHeader* header, uintptr_t headerAddress) -> std::Span<const ProgramHeader>;

    export auto getElfInfo(uintptr_t headerAddress) -> std::Optional<ElfInfo> {
        const auto* elfHeader = std::bit_cast<ElfHeader*>(headerAddress);

        const auto& identifier = elfHeader->identifier;
        const auto isElf = identifier[0] == 'E' && identifier[1] == 'L' && identifier[2] == 'F';
        if (!isElf) {
            return std::nullOptional;
        }

        if (elfHeader->type != ElfType::EXECUTABLE) {
            return std::nullOptional;
        }

        return std::Optional<ElfInfo>(getExecutableElfInfo(elfHeader, headerAddress));
    }

    auto getExecutableElfInfo(const ElfHeader* header, uintptr_t headerAddress) -> ElfInfo {
        if (header->programEntryAddress == 0) {
            return ElfInfo { extractDynamicExecutableElf(header, headerAddress) };
        }

        return ElfInfo { extractExecutableElf(header, headerAddress) };
    }

    std::size_t getProgramSize(const std::Span<const ProgramHeader> headers) {
        std::size_t memorySize = 0;
        for (const auto& header : headers) { memorySize += header.memorySize; }
        return memorySize;
    }

    auto extractExecutableElf(const ElfHeader* header, uintptr_t headerAddress) -> StaticExecutableElf {
        const auto programHeaders = extractProgramHeaders(header, headerAddress);
        const auto memorySize = getProgramSize(programHeaders);
        return StaticExecutableElf { .entryAddress = header->programEntryAddress,
                                     .headerAddress = headerAddress,
                                     .memorySize = memorySize,
                                     .programHeaders = programHeaders };
    }

    auto extractDynamicExecutableElf(const ElfHeader* header, uintptr_t headerAddress) -> DynamicExecutableElf {
        const auto programHeaders = extractProgramHeaders(header, headerAddress);
        const auto memorySize = getProgramSize(programHeaders);
        return DynamicExecutableElf { .headerAddress = headerAddress,
                                      .memorySize = memorySize,
                                      .programHeaders = programHeaders };
    }

    auto extractProgramHeaders(const ElfHeader* header, uintptr_t headerAddress) -> std::Span<const ProgramHeader> {
        const auto* programHeader = std::bit_cast<ProgramHeader*>(headerAddress + header->programHeaderOffset);
        return { programHeader, header->programHeaderCount };
    }

    void loadExecutableElf(
        uintptr_t headerAddress,
        std::Span<const ProgramHeader> programHeaders,
        uintptr_t loadAddress
    ) {
        for (const auto& programHeader : programHeaders) {
            const auto* programAddress = std::bit_cast<std::byte*>(headerAddress + programHeader.dataOffset);
            auto* memoryAddress = std::bit_cast<std::byte*>(loadAddress);
            memset(memoryAddress, 0, programHeader.memorySize);
            memcpy(memoryAddress, programAddress, programHeader.fileSize);
        }
    }

    export void loadElf(const StaticExecutableElf& elf) {
        loadExecutableElf(elf.headerAddress, elf.programHeaders, elf.entryAddress);
    }

    export void loadElf(const DynamicExecutableElf& elf, uintptr_t loadAddress) {
        loadExecutableElf(elf.headerAddress, elf.programHeaders, loadAddress);
    }
}// namespace boot
