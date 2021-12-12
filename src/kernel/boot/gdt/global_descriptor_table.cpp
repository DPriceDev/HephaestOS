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
#include "kernel/lib/libc/array.h"

namespace kernel::boot::gdt {

    //
    Array<GlobalDescriptor, 6> globalDescriptorTable;

    //
    GdtPointer gdtPointer;

    /**
     *
     */
    void initializeGlobalDescriptorTable(const GlobalDescriptor& tssDescriptor) {

        //
        globalDescriptorTable = {
            constructGlobalDescriptor(0, 0, zeroAccess, zeroFlags),
            constructGlobalDescriptor(0, MaximumMemoryLimit, codeKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, MaximumMemoryLimit, dataKernelAccess, gran32Flags),
            constructGlobalDescriptor(0, MaximumMemoryLimit, codeUserAccess, gran32Flags),
            constructGlobalDescriptor(0, MaximumMemoryLimit, dataUserAccess, gran32Flags),
            tssDescriptor
        };

        //
        gdtPointer = {
                .size = sizeof(globalDescriptorTable) - 1,
                .address = globalDescriptorTable.data()
        };

        //
        loadGdtTable(&gdtPointer);
    }
}