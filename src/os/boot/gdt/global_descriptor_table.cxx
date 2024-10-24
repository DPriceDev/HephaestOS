/* Copyright (C) 2023 David Price - All Rights Reserved
 * This file is part of HephaestOS.
 *
 * HephaestOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaestOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
 */

module;

#include "array.h"

export import os.boot.gdt.descriptor;

export module os.boot.gdt.table;

namespace boot {

    /**
    * Defines a pointer to the first Global Descriptor in an array of Global Descriptors that make
    * up the Global Descriptor table (in order). Wrapped with the size of the GDT.
    */
    export struct [[gnu::packed]] GdtPointer {

     // Size of the Global descriptor table in bytes.
     uint16_t size;

     // Pointer to the first Global descriptor in the Global descriptor table array.
     GlobalDescriptor* address;
    };

    /**
     * Segment descriptor Definitions
     */

    // Describes access for a null segment, all values are zero.
    constexpr Access zeroAccess { .accessed = false,
                                  .readWritable = false,
                                  .isConforming = false,
                                  .isExecutable = false,
                                  .descriptorType = DescriptorType::System,
                                  .privilege = Privilege::Kernel,
                                  .present = false };

    // Describes access for a Kernel Code segment, set as readable, executable, and non-conforming,
    // in ring 0.
    constexpr Access codeKernelAccess { .accessed = false,
                                        .readWritable = true,
                                        .isConforming = false,
                                        .isExecutable = true,
                                        .descriptorType = DescriptorType::CodeOrData,
                                        .privilege = Privilege::Kernel,
                                        .present = true };

    // Describes access for a Kernel Data segment, set as writable and non-conforming, in ring 0.
    constexpr Access dataKernelAccess { .accessed = false,
                                        .readWritable = true,
                                        .isConforming = false,
                                        .isExecutable = false,
                                        .descriptorType = DescriptorType::CodeOrData,
                                        .privilege = Privilege::Kernel,
                                        .present = true };

    // Describes access for a Kernel Code segment, set as readable, executable, and non-conforming,
    // in ring 3.
    constexpr Access codeUserAccess { .accessed = false,
                                      .readWritable = true,
                                      .isConforming = false,
                                      .isExecutable = true,
                                      .descriptorType = DescriptorType::CodeOrData,
                                      .privilege = Privilege::UserSpace,
                                      .present = true };

    // Describes access for a Kernel Data segment, set as writable and non-conforming, in ring 3.
    constexpr Access dataUserAccess { .accessed = false,
                                      .readWritable = true,
                                      .isConforming = false,
                                      .isExecutable = false,
                                      .descriptorType = DescriptorType::CodeOrData,
                                      .privilege = Privilege::UserSpace,
                                      .present = true };

    // Describes attributes for a null segment, all values are zero.
    constexpr Flags zeroFlags { .available = false,
                                .longMode = false,
                                .size = Size::Bit16,
                                .granularity = Granularity::Byte };

    // Describes attributes for a Code/Data segment. Segment is available, 32 bits, and uses page
    // sizing of 4Kib.
    constexpr Flags Page32BitFlags { .available = true,
                                     .longMode = false,
                                     .size = Size::Bit32,
                                     .granularity = Granularity::Page };

    // Maximum memory limit for a 32 bit os - 4GB from a 4KiB page size.
    constexpr uint32_t MaximumMemoryLimit = 0xFFFFF;

    // Array of Global Descriptors that defines the Global Descriptor Table.
    std::Array<GlobalDescriptor, 6> globalDescriptorTable {
     constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
     constructGlobalDescriptor(0, MaximumMemoryLimit, codeKernelAccess, Page32BitFlags),
     constructGlobalDescriptor(0, MaximumMemoryLimit, dataKernelAccess, Page32BitFlags),
     constructGlobalDescriptor(0, MaximumMemoryLimit, codeUserAccess, Page32BitFlags),
     constructGlobalDescriptor(0, MaximumMemoryLimit, dataUserAccess, Page32BitFlags)
    };

    // Structure holding the Global descriptor Table array pointer and size of the array.
    static const GdtPointer gdtPointer { .size = sizeof(globalDescriptorTable) - 1,
                                         .address = globalDescriptorTable.data() };

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
    export void initializeGlobalDescriptorTable(const GlobalDescriptor& tssDescriptor) {

        // Initialize the GDT with the null, kernel code, kernel data, userspace code, userspace
        // data, and tss segment descriptors.
        globalDescriptorTable[5] = tssDescriptor;

        // Load the GDT from the pointer into the CPU Registers.
        loadGdtTable(&gdtPointer);
    }
}// namespace boot