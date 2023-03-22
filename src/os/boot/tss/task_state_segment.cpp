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

#include <bit>
#include <cstdint>
#include <string.h>

#include "task_state_segment.h"

namespace kernel::boot::tss {

    //
    // todo: should be in boot class / struct?
    TssEntry tssEntry {
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
    static const uintptr_t tssEntryPtr = std::bit_cast<uintptr_t>(&tssEntry);

    /**
     *
     * @param stackPointer
     */
    void initializeTaskStateSegment(uint32_t stackPointer) {
        // Clear TSS memory to all zeroes.
        memset(&tssEntry, 0, sizeof(tssEntry));

        //
        tssEntry.esp0 = stackPointer;

        //
        loadTaskRegister(gdt::Segment::Tss, gdt::Privilege::Kernel);
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