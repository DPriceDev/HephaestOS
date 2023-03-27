/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <format.h>
#include <stdoffset.h>

namespace kernel {

    enum class MemoryType {
        MEMORY_AVAILABLE = 1,
        MEMORY_RESERVED = 2,
        MEMORY_ACPI_RECLAIMABLE = 3,
        MEMORY_NVS = 4,
        MEMORY_BAD_RAM = 5
    };

    struct [[gnu::packed]] MemoryBlock {
        uint32_t size;
        uint64_t address;
        uint64_t length;
        MemoryType type;
    };

    struct [[gnu::packed]] InitInfo {
        uintptr_t baseVirtualAddress;
        uintptr_t nextMemoryAddress;
        const std::Span<MemoryBlock>* memoryBlocks;
        uintptr_t pageDirectoryAddress;
        uintptr_t pageTableAddress;
        // todo: modules
    };

    extern "C" [[maybe_unused]] void kernelMain(
        const std::StandardOutputIterator& outputIterator,
        const InitInfo initInfo
    ) {
        std::KernelFormatOutput::getInstance().setStandardOutputIterator(outputIterator);

        std::print("INFO: HephaistOS\n");
        std::print("INFO: Version 1.0\n");

        std::print("INFO: Test {:x}", initInfo.baseVirtualAddress);
        std::print("INFO: Test {:x}", initInfo.nextMemoryAddress);

        // todo: Init process table

        // todo: create first root task

        // todo: Register ram disk root process

        // todo: Jump to ram disk main in ring 3

        // todo: Unload boot code
        // TODO: Unload this bit of kernel code?

        // todo: Remove and add an error message here, should never get here?
        while (true) { /* Endless Loop */
        }

        std::print("ERROR: Reached end of kernel code!");
    }
}// namespace kernel