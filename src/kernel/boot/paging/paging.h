// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaistOS.
//
// HephaistOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaistOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAIST_OS_KERNEL_BOOT_PAGING_PAGING_H
#define HEPHAIST_OS_KERNEL_BOOT_PAGING_PAGING_H

#include "cstdint"
#include "page_directory_entry.h"

namespace kernel::boot::paging {

    // Page directory
    static constexpr std::size_t PAGE_DIRECTORY_SIZE = 1024;
    static constexpr std::size_t PAGE_TABLE_SIZE = 1024;
    static constexpr std::size_t PAGE_SIZE = 0x1000;

    /**
     * Takes a pointer to the first entry in a @param pageDirectory and loads it to the
     * cr3 register.
     */
    extern "C" void loadPageDirectory(PageDirectoryEntry* pageDirectory);

    /**
     * Enables paging by setting the paging flag in cr0.
     */
    extern "C" void enablePaging();

    extern "C" void jumpToHigherKernel(uintptr_t address);

    /**
     * todo pass kernel mapping
     * todo pass pointers to page directory and initial page table for kernel
     * Sets up the Paging directory and identity maps the first 4mb of memory, and then
     * loads the paging directory into cr3 and enables paging.
     */
    void setupPaging(
        PageDirectoryEntry* pageDirectory,
        PageTableEntry* kernelPageTable,
        uintptr_t virtualKernelBaseAddress,
        uintptr_t kernelStartAddress,
        uintptr_t kernelEndAddress
    );
}

#endif // HEPHAIST_OS_KERNEL_BOOT_PAGING_PAGING_H
