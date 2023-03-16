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

    struct ProgramHeader {
        SegmentType segmentType;
        uint32_t dataOffset;
        uint32_t virtualMemoryOffset;
        uint32_t undefined;
        uint32_t segmentFileSize;
        uint32_t segmentMemorySize;
        ProgramFlags flags;
        uint32_t alignment;
    };

    struct ElfHeader {
        uint8_t magicNumber;
        char elfString[3];
        BitSize bitSize : 8;
        Endian endian : 8;
        uint8_t headerVersion;
        uint8_t osAbi;
        uint64_t padding;
        ElfType type : 16;
        InstructionSet instructionSet : 16;
        uint32_t elfVersion;
        uint32_t programEntryPosition;
        uint32_t programHeader;
        uint32_t sectionHeader;
        uint32_t flags;
        uint16_t headerSize;
        uint16_t programHeaderEntrySize;
        uint16_t programHeaderEntryCount;
        uint16_t sectionHeaderEntrySize;
        uint16_t sectionHeaderEntryCount;
        uint16_t sectionHeaderIndex;
    };

}

#endif //HEPHAISTOS_ELF_HEADER_H
