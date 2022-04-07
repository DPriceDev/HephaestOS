//
// Created by david on 28/11/2021.
//

#ifndef HEPHAISTOS_PAGING_H
#define HEPHAISTOS_PAGING_H

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

    /**
     * todo pass kernel mapping
     * todo pass pointers to page directory and initial page table for kernel
     * Sets up the Paging directory and identity maps the first 4mb of memory, and then
     * loads the paging directory into cr3 and enables paging.
     */
    void setupPaging();
}

#endif //HEPHAISTOS_PAGING_H
