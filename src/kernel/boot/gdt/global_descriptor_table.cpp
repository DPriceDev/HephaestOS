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
#include "kernel/klibc/string.h"
#include "kernel/boot/tss/tss.h"

namespace kernel::boot::gdt {

    // todo c++ bit shifting?
    GlobalDescriptor constructGlobalDescriptor(
            const uint32_t baseAddress,
            const uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    ) {
        return GlobalDescriptor {
                static_cast<uint16_t>((memoryLimit & 0xFFFF)),
                static_cast<uint16_t>((baseAddress & 0xFFFF)),
                static_cast<uint8_t>((baseAddress >> 16U) & 0xFF),
                access.accessed,
                access.readWritable,
                access.isConforming,
                access.isExecutable,
                access.descriptorType,
                access.privilege,
                access.present,
                static_cast<uint8_t>((memoryLimit  >> 16U) & 0xF),
                flags.available,
                flags.longMode,
                flags.size,
                flags.granularity,
                static_cast<uint8_t>((baseAddress >> 24U) & 0xFF)
        };
    }

    GdtPointer gdtPointer;

    tss::TssEntry tssEntry { };

    Array<GlobalDescriptor, 6> globalDescriptorTable = { };

    void initializeGlobalDescriptorTable(uint32_t stackPointer) {
        auto tssEntryPtr = (uint32_t) &tssEntry;

        lib::memset(&tssEntry, 0, sizeof(tssEntry));

        tssEntry = {
                .esp0 = stackPointer, // Set the kernel stack pointer.
                .ss0  = 0x10,  // Set the kernel stack segment.
                .es =  0x13,
                .cs =  0x0b,
                .ss =  0x13,
                .ds =  0x13,
                .fs =  0x13,
                .gs =  0x13, //,
                .ioMapBase = sizeof(tssEntry)
        };

        globalDescriptorTable = {
                constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
                constructGlobalDescriptor(0, 0xFFFFF, codeKernelAccess, gran32Flags),
                constructGlobalDescriptor(0, 0xFFFFF, dataKernelAccess, gran32Flags),
                constructGlobalDescriptor(0, 0xFFFFF, codeUserAccess, gran32Flags),
                constructGlobalDescriptor(0, 0xFFFFF, dataUserAccess, gran32Flags),
                // todo: move? extract this to tss
                constructGlobalDescriptor(tssEntryPtr, sizeof(tssEntry), tssEntryAccess, tssFlags)
        };

        gdtPointer = {
                sizeof(globalDescriptorTable) - 1,
                globalDescriptorTable.data()
        };
        loadGdtTable(&gdtPointer);
    }
}