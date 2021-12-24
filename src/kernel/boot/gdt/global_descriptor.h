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

    /**
     * Describes the privilege levels available in x86, mapped to the ring level. This class
     * includes Ring 0 and Ring 3 to defined the Kernel and UserSpace levels respectively.
     * Rings 1 and 2 are omitted as they are not used by the OS.
     */
    enum class Privilege {
        Kernel = 0,
        UserSpace = 3
    };

    /**
     * Describes the size of a x86 global descriptor, usually 32 bit except for the null descriptor.
     */
    enum class Size {
        Bit16 = 0,
        Bit32 = 1
    };

    /**
     * Describes the amount that the memory limit is scaled by.
     */
    enum class Granularity {
        // Limit scaled by Byte, then the limit is equivalent to its value in Bytes, i.e. a limit
        // of 100 will be 100 Bytes in size.
        Byte = 0,
        // Limit scaled by Page the limit is equivalent to its value in 4KiB Pages, i.e. a limit
        // of 100 will be 409600 Bytes or 400 Kibibytes.
        Page = 1
    };

    /**
     * Describes the type of descriptor being defined, either a system or a code/Data descriptor.
     */
    enum class DescriptorType {
        // Provides x86 specific definitions, such as a Task State Segment Descriptor.
        System = 0,
        // Used for segment descriptors which define segments of memory that defined to be used for
        // read only code, and memory available for Data segments which allows the mutable data
        // to be added and removed.
        CodeOrData = 1
    };

    /**
     * Defines the segments that are available in the Global Descriptor Table, associated to the
     * table offset that can be used to reference them.
     */
    enum class Segment {
        Null = 0x0,
        KernelCode = 0x8,
        KernelData = 0x10,
        UserSpaceCode = 0x18,
        UserSpaceData = 0x20,
        Tss = 0x28
    };

    /**
     * Structure defines a Byte sized set of access flags that are used to describe the purpose and
     * operation of the Global Descriptor.
     */
    struct [[gnu::packed]] Access {

        // CPU controlled bit, default to 0 and set to 1 by the CPU when this descriptor is accessed.
        bool accessed: 1;

        // Defines if the segment described is readable or writable.
        // For Code descriptor: flag defines if the segment is readable. Never Writable.
        // For Data descriptor: flag defines if the segment is writable. Always readable.
        bool readWritable: 1;

        // For Data segments, this is False if the segment grows up from the bottom, or True if the
        // segment grows down from the top (like a stack).
        // For Code segments, this defines if the code in this segment can be called from a different
        // privilege level. If False, it can only be called from the same level, i.e. Ring 0 runs
        // only Ring 0, not ring 3.
        // If True, then lower privileges can far jump to higher levels, i.e. Ring 3 to Ring 2;
        // however, Ring 0 cannot far jump to Ring 2. Also, if this is true, then the Privilege
        // level will not change after a far jump.
        bool isConforming: 1;

        // True if this is a Code segment, False if it is a Data segment.
        bool isExecutable: 1;

        // Defines if this is a System (i.e. TSS), or Code/Data Segment.
        DescriptorType descriptorType: 1;

        // Defines the ring level that has access to this segment. Has access to this level and above.
        Privilege privilege: 2;

        // Defines a valid segment, always true except for the null descriptor.
        bool present: 1;
    };

    /**
     * Set of Flags that describe a attributes of the Global Descriptor.
     */
    struct [[gnu::packed]] Flags {

        // Denotes if the segment can be accessed. True for Code/Data segments, false for System.
        bool available: 1;

        // Defines this is a 64 bit descriptor.
        bool longMode: 1;

        // Denotes if the descriptor is 16 bit or 32 bit in size.
        Size size: 1;

        // Defines the limit should be scaled by Bytes or Pages.
        Granularity granularity: 1;
    };

    /**
     * Global Descriptor describes the memory location and size of a Segment, whether it is a code,
     * data, or system segment, and the attributes that describe its use, size and access.
     */
    struct [[gnu::packed]] GlobalDescriptor {

        // Lower 8 bits of the memory limit.
        uint16_t lowerLimit;

        // Lower 8 bits of the base address.
        uint32_t lowerBase: 16;

        // Middle 8 bits of the base address.
        uint32_t midBase: 8;

        // Defines the access to the segment and its operation.
        Access access;

        // Upper 8 bits of the memory limit.
        uint8_t upperLimit: 4;

        // Denotes if the segment can be accessed. True for Code/Data segments, false for System.
        bool available: 1;

        // Defines this is a 64 bit descriptor.
        bool longMode: 1;

        // Denotes if the descriptor is 16 bit or 32 bit in size.
        Size size: 1;

        // Defines the limit should be scaled by Bytes or Pages.
        Granularity granularity: 1;

        // Upper 8 bits of the base address.
        uint8_t upperBase;
    };

    /**
     * Constructs a Global descriptor that can be inserted in a Global descriptor table. This takes
     * a set of addresses, sizes, flags and settings to define a Global Descriptor. The x86
     * implementation of the Global Descriptor splits the base address and limit across the
     * structure; therefore the lower, mid, and upper sections of the baseAddress and memoryLimit
     * are bit-masked and bit-shifted into place.
     *
     * @param baseAddress is the memory address that this segment will begin at.
     * @param memoryLimit is the size of the segment in bytes.
     * @param access describe the type of segment, privilege and other parameters.
     * @param flags describe the size (16 or 32 bit) and granularity (bit or page) of the descriptor.
     * @return Global Descriptor constructed from the parameters.
     */
    GlobalDescriptor constructGlobalDescriptor(
            uint32_t baseAddress,
            uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    );
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H