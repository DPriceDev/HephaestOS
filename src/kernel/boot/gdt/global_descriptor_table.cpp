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
#include "kernel/lib/libc/array.h"
#include "kernel/lib/libc/string.h"
#include "kernel/boot/tss/tss.h"

namespace kernel::boot::gdt {

    constexpr uint16_t Mask16Bit = 0xFFFF;
    constexpr uint8_t Mask8Bit = 0xFF;
    constexpr uint8_t Mask4Bit = 0xF;

    constexpr uint8_t Offset16Bit = 16U;
    constexpr uint8_t Offset24Bit = 24U;

    // todo c++ bit shifting?
    GlobalDescriptor constructGlobalDescriptor(
            const uint32_t baseAddress,
            const uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    ) {
        return GlobalDescriptor{
                .lowerLimit     = static_cast<uint16_t>((memoryLimit & Mask16Bit)),
                .lowerBase      = static_cast<uint16_t>((baseAddress & Mask16Bit)),
                .midBase        = static_cast<uint8_t>((baseAddress >> Offset16Bit) & Mask8Bit),
                .access         = access,
                .upperLimit     = static_cast<uint8_t>((memoryLimit >> Offset16Bit) & Mask4Bit),
                .available      = flags.available,
                .longMode       = flags.longMode,
                .size           = flags.size,
                .granularity    = flags.granularity,
                .upperBase      = static_cast<uint8_t>((baseAddress >> Offset24Bit) & Mask8Bit)
        };
    }

    GdtPointer gdtPointer;

    tss::TssEntry tssEntry { };

    Array<GlobalDescriptor, 6> globalDescriptorTable = { };

    void initializeGlobalDescriptorTable(uint32_t stackPointer) {
        auto tssEntryPtr = (uint32_t) &tssEntry;

        // Clear TSS memory to all zeroes.
        lib::memset(&tssEntry, 0, sizeof(tssEntry));

        tssEntry = {
                .esp0 = stackPointer,           // Set the kernel stack pointer.
                .ss0  = 0x10,                   // Set the kernel stack segment.
                .es =  0x13,                    //
                .cs =  0x0b,
                .ss =  0x13,
                .ds =  0x13,
                .fs =  0x13,
                .gs =  0x13,
                .ioMapBase = sizeof(tssEntry)
        };

        globalDescriptorTable = {
                constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
                constructGlobalDescriptor(0, MaximumMemoryLimit, codeKernelAccess, gran32Flags),
                constructGlobalDescriptor(0, MaximumMemoryLimit, dataKernelAccess, gran32Flags),
                constructGlobalDescriptor(0, MaximumMemoryLimit, codeUserAccess, gran32Flags),
                constructGlobalDescriptor(0, MaximumMemoryLimit, dataUserAccess, gran32Flags),
                // todo: move? extract this to tss
                constructGlobalDescriptor(tssEntryPtr, sizeof(tssEntry), tssEntryAccess, tssFlags)
        };

        gdtPointer = {
            .size = sizeof(globalDescriptorTable) - 1,
            .address = globalDescriptorTable.data()
        };

        loadGdtTable(&gdtPointer);
    }
}