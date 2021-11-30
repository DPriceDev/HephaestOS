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

#include "global_descriptor_table.h"
#include "kernel/klibc/array.h"
#include "kernel/boot/tss/tss.h"

namespace kernel::boot::gdt {

    // todo: move? extract this to tss
    tss::TssEntry tssEntry { };

    // todo c++ bit shifting?
    GlobalDescriptor constructGlobalDescriptor(
            const uint32_t baseAddress,
            const uint32_t memoryLimit,
            const Access &access,
            const Flags &flags,
            const bool available
    ) {
        return GlobalDescriptor {
                static_cast<uint16_t>((memoryLimit & 0xFFFF)),
                static_cast<uint16_t>((baseAddress & 0xFFFFFF)),
                access,
                static_cast<uint8_t>((memoryLimit & 0xF0000) >> 16U),
                available,
                false,
                flags.size,
                flags.granularity,
                static_cast<uint8_t>((baseAddress & 0xF000000) >> 24U)
        };
    }

    GdtPointer gdtPointer;

    Array<GlobalDescriptor, 6> globalDescriptorTable = { };

    void initializeGlobalDescriptorTable(uint32_t stackPointer) {
        tssEntry = {
                .esp0 = 0, // Set the kernel stack pointer.
                .ss0  = 0x10,  // Set the kernel stack segment.
                .es = 0x0b,
                .cs = 0x0b,
                .ss = 0x0b,
                .ds = 0x0b,
                .fs = 0x0b,
                .gs = 0x13,
                .ioMapBase = 104
        };

        auto tssEntryPtr = (uint32_t) &tssEntry;

        globalDescriptorTable = {
                constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags, true),
                constructGlobalDescriptor(0, 0xFFFFF, codeKernelAccess, gran32Flags, true),
                constructGlobalDescriptor(0, 0xFFFFF, dataKernelAccess, gran32Flags, true),
                constructGlobalDescriptor(0, 0xFFFFF, codeUserAccess, gran32Flags, true),
                constructGlobalDescriptor(0, 0xFFFFF, dataUserAccess, gran32Flags, true),
                // todo: move? extract this to tss
                constructGlobalDescriptor(tssEntryPtr, tssEntryPtr + sizeof(tssEntry), tssEntryAccess, zeroFlags, false)
        };

        gdtPointer = {
                sizeof(globalDescriptorTable) - 1,
                globalDescriptorTable.data()
        };
        loadGdtTable(&gdtPointer);
    }
}