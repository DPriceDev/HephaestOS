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

    /**
     * Defines a pointer to the first Global Descriptor in an array of Global Descriptors that make
     * up the Global Descriptor table (in order). Wrapped with the size of the GDT.
     */
    struct [[gnu::packed]] GdtPointer {

        // Size of the Global descriptor table in bytes.
        uint16_t size;

        // Pointer to the first Global descriptor in the Global descriptor table array.
        GlobalDescriptor* address;
    };

    /**
     * Segment descriptor Definitions
     */

    // Describes access for a null segment, all values are zero.
    constexpr Access zeroAccess {
            .accessed = false,
            .readWritable = false,
            .isConforming = false,
            .isExecutable = false,
            .descriptorType = DescriptorType::System,
            .privilege = Privilege::Kernel,
            .present = false
    };

    // Describes access for a Kernel Code segment, set as readable, executable, and non-conforming,
    // in ring 0.
    constexpr Access codeKernelAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = true,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::Kernel,
            .present = true
    };

    // Describes access for a Kernel Data segment, set as writable and non-conforming, in ring 0.
    constexpr Access dataKernelAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = false,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::Kernel,
            .present = true
    };

    // Describes access for a Kernel Code segment, set as readable, executable, and non-conforming,
    // in ring 3.
    constexpr Access codeUserAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = true,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::UserSpace,
            .present = true
    };

    // Describes access for a Kernel Data segment, set as writable and non-conforming, in ring 3.
    constexpr Access dataUserAccess {
            .accessed = false,
            .readWritable = true,
            .isConforming = false,
            .isExecutable = false,
            .descriptorType = DescriptorType::CodeOrData,
            .privilege = Privilege::UserSpace,
            .present = true
    };

    // Describes attributes for a null segment, all values are zero.
    constexpr Flags zeroFlags {
            .available = false,
            .longMode = false,
            .size = Size::Bit16,
            .granularity = Granularity::Byte
    };

    // Describes attributes for a Code/Data segment. Segment is available, 32 bits, and uses page
    // sizing of 4Kib.
    constexpr Flags Page32BitFlags {
            .available = true,
            .longMode = false,
            .size = Size::Bit32,
            .granularity = Granularity::Page
    };

    // Maximum memory limit for a 32 bit system - 4GB from a 4KiB page size.
    constexpr uint32_t MaximumMemoryLimit = 0xFFFFF;

    /**
     * Methods
     */

    /**
     * Call to load a Global Descriptor Table, passed as a GDTPointer, into the CPU registers.
     *
     * @param pointer points to the Global descriptor tables pointer and size.
     */
    extern "C" void loadGdtTable(const GdtPointer* pointer);

    /**
     * Initializes the CPU's Global Descriptor Table with the minimum required segments for the
     * kernel and userspace to be initialized.
     * The first descriptor is a null descriptor to meet the x86 requirements.
     * Then a Code and Data descriptor is added for the Kernel segments, covering the full memory
     * space and a privilege level of 0.
     * Then a Code and Data descriptor is added for the Userspace segments, covering the full memory
     * space and a privilege level of 3.
     * And lastly a Task State Segment descriptor to define the one TSS required for software task
     * switching.
     *
     * @param tssDescriptor provides the task state segments descriptor to be added to the array.
     */
    void initializeGlobalDescriptorTable(const GlobalDescriptor& tssDescriptor);
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H
