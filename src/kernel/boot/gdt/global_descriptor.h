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

    enum class Privilege {
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

    enum class Segment {
        Null = 0x0,
        KernelCode = 0x8,
        KernelData = 0x10,
        UserSpaceCode = 0x18,
        UserSpaceData = 0x20,
        Tss = 0x28
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
        Privilege privilege: 2;
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

    // Methods
    GlobalDescriptor constructGlobalDescriptor(
            uint32_t baseAddress,
            uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    );
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H