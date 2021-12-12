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

#ifndef HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H
#define HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H

#include <kernel/lib/libc/stdint.h>
#include "global_descriptor.h"

namespace kernel::boot::gdt {

    struct [[gnu::packed]] GdtPointer {
        uint16_t size;
        GlobalDescriptor* address;
    };

    /**
     * Segment descriptor Definitions
     */

    constexpr Access zeroAccess {
            .accessed = false,
            .readWritable = false,
            .isConforming = false,
            .isExecutable = false,
            .descriptorType = DescriptorType::System,
            .privilege = Privilege::Kernel,
            .present = false
    };

    constexpr Access codeKernelAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = true,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::Kernel,
            .present = true
    };
    constexpr Access dataKernelAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = false,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::Kernel,
            .present = true
    };

    constexpr Access codeUserAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = true,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::UserSpace,
            .present = true
    };
    constexpr Access dataUserAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = false,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::UserSpace,
            .present = true
    };

    constexpr Flags zeroFlags {
            .available = false,
            .longMode = false,
            .size = Size::Bit16,
            .granularity = Granularity::Bit
    };

    constexpr Flags gran32Flags {
            .available = true,
            .longMode = false,
            .size = Size::Bit32,
            .granularity = Granularity::Page
    };

    constexpr uint32_t MaximumMemoryLimit = 0xFFFFF;

    void initializeGlobalDescriptorTable(const GlobalDescriptor& tssDescriptor);

    extern "C" void loadGdtTable(const GdtPointer* pointer);
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H
