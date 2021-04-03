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

    struct GlobalDescriptorAccess {
        uint8_t present: 1;
        uint8_t privilege: 2;
        uint8_t descriptorType: 1;
        uint8_t isExecutable: 1;
        uint8_t directionConform: 1;
        uint8_t ReadWritable: 1;
        uint8_t accessed: 1;
    } __attribute__((aligned(8))) __attribute__ ((packed));

    struct GlobalDescriptorFlags {
        uint8_t granularity: 1;
        uint8_t size: 1;
    } __attribute__((aligned(2))) __attribute__ ((packed));

    struct GlobalDescriptor {
        uint16_t lowerLimit;
        uint16_t lowerBase;
        uint8_t middleBase;
        GlobalDescriptorAccess access;
        uint8_t upperLimit: 4;
        GlobalDescriptorFlags flags;
        uint8_t upperBase;
    } __attribute__((aligned(32)))__attribute__ ((packed));


    static constexpr auto zeroAccess = GlobalDescriptorAccess{0, 0, 0, 0, 0, 0, 0};
    static constexpr auto codeKernelAccess = GlobalDescriptorAccess{1, 0, 1, 1, 1, 1, 1};
    static constexpr auto dataKernelAccess = GlobalDescriptorAccess{1, 0, 1, 1, 1, 1, 1};

    static constexpr auto zeroFlags = GlobalDescriptorFlags{0, 0};
    static constexpr auto gran32Flags = GlobalDescriptorFlags{1, 1};

    extern "C" void setGlobalDescriptorTable(const GlobalDescriptor tablePointer[], uint16_t tableSize);

    static constexpr GlobalDescriptor constructGlobalDescriptor(int32_t baseAddress,
                                                                int32_t memoryLimit,
                                                                const GlobalDescriptorAccess &access,
                                                                const GlobalDescriptorFlags &flags) {
        GlobalDescriptor globalDescriptor{
                static_cast<uint16_t>((memoryLimit & 0xFFFF)),
                static_cast<uint16_t>((baseAddress & 0xFFFF)),
                static_cast<uint8_t>((baseAddress & 0xFF0000) >> 16),
                access,
                static_cast<uint8_t>((memoryLimit & 0xF0000) >> 16),
                flags,
                static_cast<uint8_t>((baseAddress & 0xFF000000) >> 24)
        };

        return globalDescriptor;
    }

    static constexpr GlobalDescriptor globalDescriptorTable[] = {
            constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
            constructGlobalDescriptor(0, 0x000FFFFF, codeKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, 0x000FFFFF, dataKernelAccess, gran32Flags)
    };
}

#endif // HEPHAIST_OS_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H
