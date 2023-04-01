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

#ifndef HEPHAEST_OS_ELF_H
#define HEPHAEST_OS_ELF_H

#include <array.h>
#include <cstdint>
#include <span.h>

namespace boot {

    enum class BitSize { BIT_32 = 1, BIT_64 = 2 };

    enum class Endian { LITTLE = 1, BIG = 2 };

    enum class ElfType { RELOCATABLE = 1, EXECUTABLE = 2, SHARED = 3, CORE = 4 };

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

    // todo: Might need to be struct
    enum class ProgramFlags { EXECUTABLE = 1, WRITABLE = 2, READABLE = 4 };

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

    enum class SectionType {
        UNUSED = 0,
        PROGRAM_DATA = 1,
        SYMBOL_TABLE = 2,
        STRING_TABLE = 3,
        RELOCATION_WITH_ADDENDS = 4,
        HASH_TABLE = 5,
        DYNAMIC_LINK_INFO = 6,
        NOTES = 7,
        BSS = 8,
        RELOCATION_WITHOUT_ADDENDS = 9,
        SHLIB_RESERVED = 0x0A,
        DYNAMIC_LINK_SYMBOL_TABLE = 0x0B,
        CONSTRUCTORS = 0x0E,
        DESTRUCTORS = 0x0F,
        PRE_CONSTRUCTORS = 0x10,
        GROUP = 0x11,
        EXTENDED_SECTION_INDICES = 0x12,
        DEFINED_TYPES = 0x13
    };

    struct SectionFlags {
        bool isWritable : 1;
        bool isAllocated : 1;
        bool isInstructions : 1;
        bool : 1;
        bool canBeMerged : 1;
        bool containsStrings : 1;
        bool containsSHTIndex : 1;
        bool preserveLinkOrder : 1;
        bool isNonOSConforming : 1;
        bool isInGroup : 1;
        bool hasThreadLocalStorage : 1;
        uint32_t : 19;
        bool isOrdered : 1;
        bool isExcluded : 1;
    };

    struct [[gnu::packed]] SectionHeader {
        const char* name;
        SectionType type;
        SectionFlags flags;
        uintptr_t virtualAddress;
        uintptr_t offset;
        size_t fileSize;
        uint32_t linkIndex;
        uint32_t info;
        size_t alignment;
        size_t entrySize;
    };

    constexpr size_t ELF_HEADER_PADDING = 7;

    struct [[gnu::packed]] ElfHeader {
        uint8_t magicNumber;
        uint8_t identifier[3];
        BitSize bitSize : 8;
        Endian endian : 8;
        uint8_t headerVersion;
        uint8_t osAbi;
        uint8_t abiVersion;
        uint8_t padding[ELF_HEADER_PADDING];
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
}// namespace boot

#endif// HEPHAEST_OS_ELF_H
