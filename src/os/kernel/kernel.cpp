/* Copyright (C) 2023 David Price - All Rights Reserved
 * This file is part of HephaestOS.
 *
 * HephaestOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaestOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <format.h>

import os.kernel.thread.id;
import os.kernel.thread.table;

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
        uintptr_t virtualBase;
        uintptr_t nextMemory;
        const std::Span<MemoryBlock>* memoryBlocks;
        uintptr_t pageDirectory;
        uintptr_t pageTable;
        // todo: modules
        uintptr_t stack;
    };

    extern "C" [[maybe_unused]] void
        kernelMain(const std::StandardOutputIterator& outputIterator, const InitInfo initInfo) {
        std::KernelFormatOutput::getInstance().setStandardOutputIterator(outputIterator);

        std::print("INFO: HephaestOS\n");
        std::print("INFO: Version 1.0\n");

        // todo: need to store this somewhere, inject? singleton?
        auto threadTable = ThreadTable();

        auto threadIDProvider = ThreadIDProvider();
        auto initialTCB = ThreadControlBlock {
            .id = threadIDProvider.getId(), .stack = initInfo.stack,
            // todo: add instruction pointer (point to initial task module)
        };
        const auto isRegistered = threadTable.registerThreadControlBlock(&initialTCB);
        if (!isRegistered) {
            std::print("ERROR: Failed to register initial TCB in Thread table");
            return;
        }

        // todo: Do I need to setup the TSS here with the stack info?

        // todo: enter intial task by jumping to instruction pointer and userspace

        // todo: Unload boot code and unused code

        // todo: Remove and add an error message here, should never get here?
        while (true) { /* Endless Loop */
        }

        std::print("ERROR: Reached end of kernel code!");
    }
}// namespace kernel