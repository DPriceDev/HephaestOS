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

#ifndef HEPHAIST_OS_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H
#define HEPHAIST_OS_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H

#include "kernel/types.h"

namespace kernel::gdt {

    struct Access {
        uint8_t present: 1;
        uint8_t privilege: 2;
        uint8_t descriptorType: 1;
        uint8_t isExecutable: 1;
        uint8_t directionConform: 1;
        uint8_t ReadWritable: 1;
        uint8_t accessed: 1;
    } __attribute__((packed, aligned(8)));

    struct Flags {
        uint8_t granularity: 1;
        uint8_t size: 1;
    } __attribute__((packed, aligned(2)));

    struct GlobalDescriptor {
        uint16_t lowerLimit;
        uint16_t lowerBase;
        uint8_t middleBase;
        Access access;
        uint8_t upperLimit: 4;
        Flags flags;
        uint8_t upperBase;
    } __attribute__((aligned(32)));


    static constexpr auto zeroAccess = Access{0, 0, 0, 0, 0, 0, 0};
    static constexpr auto codeKernelAccess = Access{1, 0, 1, 1, 1, 1, 1};
    static constexpr auto dataKernelAccess = Access{1, 0, 1, 1, 1, 1, 1};

    static constexpr auto zeroFlags = Flags{0, 0};
    static constexpr auto gran32Flags = Flags{1, 1};

    extern "C" void setGlobalDescriptorTable(const GlobalDescriptor tablePointer[], uint16_t tableSize);

    static constexpr GlobalDescriptor constructGlobalDescriptor(uint32_t baseAddress,
                                                                uint32_t memoryLimit,
                                                                const Access &access,
                                                                const Flags &flags) {
        GlobalDescriptor globalDescriptor{
                static_cast<uint16_t>((memoryLimit & 0xFFFF)),
                static_cast<uint16_t>((baseAddress & 0xFFFF)),
                static_cast<uint8_t>((baseAddress & 0xFF0000) >> 16U),
                access,
                static_cast<uint8_t>((memoryLimit & 0xF0000) >> 16U),
                flags,
                static_cast<uint8_t>((baseAddress & 0xFF000000) >> 24U)
        };

        return globalDescriptor;
    }

    static constexpr GlobalDescriptor globalDescriptorTable[] = {
            constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
            constructGlobalDescriptor(0, 0x000FFFFF, codeKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, 0x000FFFFF, dataKernelAccess, gran32Flags)
    };

    static void initializeGlobalDescriptorTable() {
        uint16_t tableSize = sizeof(globalDescriptorTable) / sizeof(GlobalDescriptor);
        setGlobalDescriptorTable(globalDescriptorTable, tableSize);
    }
}

#endif // HEPHAIST_OS_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H
