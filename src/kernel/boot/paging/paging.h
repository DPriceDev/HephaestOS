//
// Created by david on 28/11/2021.
//

#ifndef HEPHAISTOS_PAGING_H
#define HEPHAISTOS_PAGING_H

#include "cstdint"
#include "page_directory_entry.h"

namespace kernel::boot::paging {

    static constexpr std::size_t PAGE_DIRECTORY_SIZE = 1024;
    static constexpr std::size_t PAGE_TABLE_SIZE = 1024;

    extern "C" void loadPageDirectory(PageDirectoryEntry* pageDirectory);
    extern "C" void enablePaging();

    void setupPaging();
}

#endif //HEPHAISTOS_PAGING_H
