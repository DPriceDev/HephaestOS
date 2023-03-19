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

#ifndef HEPHAISTOS_ELF_HEADER_H
#define HEPHAISTOS_ELF_HEADER_H

#include <cstdint>
#include <array.h>
#include <span.h>

namespace kernel::boot::elf {

    enum class BitSize {
        BIT_32 = 1,
        BIT_64 = 2
    };

    enum class Endian {
        LITTLE = 1,
        BIG = 2
    };

    enum class ElfType {
        RELOCATABLE = 1,
        EXECUTABLE = 2,
        SHARED = 3,
        CORE = 4
    };

    enum class InstructionSet {
        UNSPECIFIED = 0,
        SPARC = 2,
        X86 = 3,
        MIPS = 8,
        POWER_PC = 0x14,
        ARM = 0x28,
        SUPER_H = 0x2A,
        IA_64 = 0x32,
        X86_64 = 0x3E,
        A_ARCH_64 = 0xB7,
        RISC_V = 0xF3
    };

    enum class SegmentType {
        NONE = 0,
        LOAD = 1,
        DYNAMIC = 2,
        INTERPRETER = 3,
        NOTE = 4,

    };

    enum class ProgramFlags {
        EXECUTABLE = 1,
        WRITABLE = 2,
        READABLE = 4
    };

    struct [[gnu::packed]] ProgramHeader {
        SegmentType segmentType;
        uint32_t dataOffset;
        uint32_t virtualAddress;
        uint32_t physicalAddress;
        uint32_t fileSize;
        uint32_t memorySize;
        ProgramFlags flags;
        uint32_t alignment;
    };

    constexpr size_t ELF_HEADER_PADDING = 7;

    struct [[gnu::packed]] ElfHeader {
        uint8_t magicNumber;
        std::Array<uint8_t, 3> identifier;
        BitSize bitSize : 8;
        Endian endian : 8;
        uint8_t headerVersion;
        uint8_t osAbi;
        uint8_t abiVersion;
        std::Array<uint8_t, ELF_HEADER_PADDING> padding;
        ElfType type : 16;
        InstructionSet instructionSet : 16;
        uint32_t elfVersion;
        uint32_t programEntryAddress;
        uint32_t programHeaderOffset;
        uint32_t sectionHeaderOffset;
        uint32_t flags;
        uint16_t headerSize;
        uint16_t programHeaderSize;
        uint16_t programHeaderCount;
        uint16_t sectionHeaderSize;
        uint16_t sectionHeaderCount;
        uint16_t sectionHeaderIndex;
    };
}

#endif //HEPHAISTOS_ELF_HEADER_H
