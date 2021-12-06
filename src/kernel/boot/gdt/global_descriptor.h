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

#ifndef HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H
#define HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H

namespace kernel::boot::gdt {

    // Global Descriptor Models

    enum class DescriptorPrivilege {
        Kernel = 0,
        UserSpace = 3
    };

    enum class Size {
        Bit16 = 0,
        Bit32 = 1
    };

    enum class Granularity {
        Bit = 0,
        Page = 1
    };

    enum class DescriptorType {
        System = 0,
        CodeOrData = 1
    };

    /**
     *
     */
    struct [[gnu::packed]] Access {
        bool accessed: 1;
        bool readWritable: 1;
        bool isConforming: 1;
        bool isExecutable: 1;
        DescriptorType descriptorType: 1;
        DescriptorPrivilege privilege: 2;
        bool present: 1;
    };

    /**
     *
     */
    struct [[gnu::packed]] Flags {
        bool available: 1;
        bool longMode: 1;
        Size size: 1;
        Granularity granularity: 1;
    };

    /**
     *
     */
    struct [[gnu::packed]] GlobalDescriptor {
        uint16_t lowerLimit;
        uint32_t lowerBase: 16;
        uint32_t midBase: 8;
        Access access;
        uint8_t upperLimit: 4;
        bool available: 1;
        bool longMode: 1;
        Size size: 1;
        Granularity granularity: 1;
        uint8_t upperBase;
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
        .privilege = DescriptorPrivilege::Kernel,
        .present = false
    };

    constexpr Access codeKernelAccess {
        .accessed = false,
        .readWritable = true,
        .isConforming = false,
        .isExecutable = true,
        .descriptorType = DescriptorType::CodeOrData,
        .privilege = DescriptorPrivilege::Kernel,
        .present = true
    };
    constexpr Access dataKernelAccess {
        .accessed = false,
        .readWritable = true,
        .isConforming = false,
        .isExecutable = false,
        .descriptorType = DescriptorType::CodeOrData,
        .privilege = DescriptorPrivilege::Kernel,
        .present = true
    };

    constexpr Access codeUserAccess {
        .accessed = false,
        .readWritable = true,
        .isConforming = false,
        .isExecutable = true,
        .descriptorType = DescriptorType::CodeOrData,
        .privilege = DescriptorPrivilege::UserSpace,
        .present = true
    };
    constexpr Access dataUserAccess {
        .accessed = false,
        .readWritable = true,
        .isConforming = false,
        .isExecutable = false,
        .descriptorType = DescriptorType::CodeOrData,
        .privilege = DescriptorPrivilege::UserSpace,
        .present = true
    };

    constexpr Access tssEntryAccess {
        .accessed = true,
        .readWritable = false,
        .isConforming = false,
        .isExecutable = true,
        .descriptorType = DescriptorType::System,
        .privilege = DescriptorPrivilege::Kernel,
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

    constexpr Flags tssFlags {
        .available = false,
        .longMode = false,
        .size = Size::Bit16,
        .granularity = Granularity::Bit
    };
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H