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
#include "array.h"

namespace boot {

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
    void initializeGlobalDescriptorTable(const GlobalDescriptor& tssDescriptor) {

        // Initialize the GDT with the null, kernel code, kernel data, userspace code, userspace
        // data, and tss segment descriptors.
        globalDescriptorTable[5] = tssDescriptor;

        // Load the GDT from the pointer into the CPU Registers.
        loadGdtTable(&gdtPointer);
    }
}// namespace boot