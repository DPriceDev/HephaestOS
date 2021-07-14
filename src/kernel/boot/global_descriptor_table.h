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

    struct GdtPointer {
        uint16_t size;
        uint32_t address;
    } __attribute__((packed));

    struct Access {
        uint8_t accessed : 1;
        uint8_t ReadWritable : 1;
        uint8_t isConforming : 1;
        uint8_t isExecutable : 1;
        uint8_t descriptorType : 1;
        uint8_t privilege : 2;
        uint8_t present : 1;
    } __attribute__((packed));

    struct Flags {
        uint8_t unused : 2;
        uint8_t size : 1;
        uint8_t granularity : 1;
    } __attribute__((packed));

    struct GlobalDescriptor {
        uint16_t lowerLimit;
        uint32_t lowerBase : 24;
        //uint8_t middleBase;
        Access access;
        uint8_t upperLimit: 4;
        uint8_t available : 1;
        uint8_t longMode : 1;
        uint8_t size : 1;
        uint8_t granularity : 1;
        uint8_t upperBase;
    } __attribute__((packed));

    static constexpr auto zeroAccess = Access{0, 0, 0, 0, 0, 0, 0};
    static constexpr auto codeKernelAccess = Access{0, 1, 1, 1, 1, 0, 1};
    static constexpr auto dataKernelAccess = Access{0, 1, 1, 0, 1, 0, 1};
    static constexpr auto codeUserAccess = Access{0, 1, 1, 1, 1, 3, 1};
    static constexpr auto dataUserAccess = Access{0, 1, 1, 0, 1, 3, 1};

    static constexpr auto zeroFlags = Flags{0, 0, 0};
    static constexpr auto gran32Flags = Flags{0, 1, 1};

    extern "C" void setGlobalDescriptorTable(const GlobalDescriptor tablePointer[], uint16_t tableSize);

    extern "C" void gdtFlush(uint32_t pointer);

    static constexpr GlobalDescriptor constructGlobalDescriptor(
            uint32_t baseAddress,
            uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    ) {
        GlobalDescriptor globalDescriptor{
                static_cast<uint16_t>((memoryLimit & 0xFFFF)),
                static_cast<uint16_t>((baseAddress & 0xFFFFFF)),
                access,
                static_cast<uint8_t>((memoryLimit & 0xF0000) >> 16U),
                1,
                0,
                flags.size,
                flags.granularity,
                static_cast<uint8_t>((baseAddress & 0xF000000) >> 24U)
        };

        return globalDescriptor;
    }

    static constexpr GlobalDescriptor globalDescriptorTable[] = {
            constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
            constructGlobalDescriptor(0, 0xFFFFF, codeKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, 0xFFFFF, dataKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, 0xFFFFF, codeUserAccess, gran32Flags),
            constructGlobalDescriptor(0, 0xFFFFF, dataUserAccess, gran32Flags)
    };

    const GdtPointer gdtPointer = GdtPointer {
            sizeof(globalDescriptorTable) - 1,
            (uint32_t) &globalDescriptorTable
    };

    static void initializeGlobalDescriptorTable() {
        gdtFlush((uint32_t) &gdtPointer);
    }
}

#endif // HEPHAIST_OS_KERNEL_GLOBAL_DESCRIPTOR_TABLE_H
