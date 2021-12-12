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

#include <kernel/lib/libc/stdint.h>
#include <kernel/lib/libc/string.h>

#include "task_state_segment.h"

namespace kernel::boot::tss {

    //
    TssEntry tssEntry;

    //
    const uintptr_t tssEntryPtr = reinterpret_cast<uintptr_t>(&tssEntry);

    /**
     *
     * @param stackPointer
     */
    void initializeTaskStateSegment(uint32_t stackPointer) {
        // Clear TSS memory to all zeroes.
        lib::memset(&tssEntry, 0, sizeof(tssEntry));

        //
        tssEntry = {
                .esp0 = stackPointer,           // Set the kernel stack pointer.
                .ss0  = 0x10,                   // Set the kernel stack segment.
                .es =  0x13,                    //
                .cs =  0x0b,
                .ss =  0x13,
                .ds =  0x13,
                .fs =  0x13,
                .gs =  0x13,
                .ioMapBase = sizeof(tss::TssEntry)
        };

        //
        loadTaskRegister();
    }

    /**
     *
     * @return
     */
    auto getTaskStateSegmentDescriptor() -> gdt::GlobalDescriptor {
        //
        return constructGlobalDescriptor(tssEntryPtr, sizeof(tss::TssEntry), tssEntryAccess, tssFlags);
    }
}