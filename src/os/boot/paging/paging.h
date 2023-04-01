// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAEST_OS_KERNEL_BOOT_PAGING_PAGING_H
#define HEPHAEST_OS_KERNEL_BOOT_PAGING_PAGING_H

#include "cstdint"
#include "grub/multiboot_info.h"
#include "model/page_directory_entry.h"

namespace boot {

    /**
     * Takes a pointer to the first entry in a @param pageDirectory and loads it to the
     * cr3 register.
     */
    extern "C" void loadPageDirectory(PageDirectoryEntry* pageDirectory);

    /**
     * Enables paging by setting the paging flag in cr0.
     */
    extern "C" void enablePaging();

    /**
     * Sets up the Paging directory and identity maps the first 4mb of memory, and then
     * loads the paging directory into cr3 and enables paging.
     */
    extern "C" void initializePaging(
        MultiBootInfo* info,
        PageDirectoryEntry* pageDirectory,
        PageTableEntry* kernelPageTable,
        uintptr_t virtualKernelBaseAddress,
        uintptr_t kernelStartAddress,
        uintptr_t kernelEndAddress
    );

    void mapAddressRangeInTable(
        PageTableEntry* pageTablePointer,
        uintptr_t virtualStartAddress,
        uintptr_t startAddress,
        uintptr_t endAddress
    );

    void unmapLowerKernel(PageDirectoryEntry* pageDirectoryPointer);
}// namespace boot

#endif// HEPHAEST_OS_KERNEL_BOOT_PAGING_PAGING_H
