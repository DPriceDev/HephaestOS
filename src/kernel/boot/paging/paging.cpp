//
// Created by david on 28/11/2021.
//

#include "paging.h"
#include <cstdint>
#include <array.h>
#include <algorithms.h>

#include "page_directory_entry.h"

namespace kernel::boot::paging {

    // todo: Move to static?
    std::Array<PageDirectoryEntry, PAGE_DIRECTORY_SIZE> pageDirectory __attribute__((aligned(4096)));
    std::Array<PageTableEntry, PAGE_TABLE_SIZE> firstPageTable __attribute__((aligned(4096)));

    void setupPaging() {

        auto* pageD = &pageDirectory;
        auto* pageT = &firstPageTable;

        auto* pageDD = pageDirectory.data();
        auto* pageTD = firstPageTable.data();

        // todo: model the page directory?
        std::forEach(pageDirectory.begin(), pageDirectory.end(), [] (auto & element) {
            // This sets the following flags to the pages:
            //   Supervisor: Only kernel-mode can access them
            //   Write Enabled: It can be both read from and written to
            //   Not Present: The page table is not present
            element = PageDirectoryEntry {
                .access = PageDirectoryAccess {
                        .canWrite = true
                },
            };
        });

        // holds the physical address where we want to start mapping these pages to.
        // in this case, we want to map these pages to the very beginning of memory.

        // todo: ForEachIndexed ?

        //we will fill all 1024 entries in the table, mapping 4 megabytes
        // todo: model page table
        uint32_t address = 0;
        std::forEach(firstPageTable.begin(), firstPageTable.end(), [&address] (auto & entry) {
            // As the address is page aligned, it will always leave 12 bits zeroed.
            // Those bits are used by the attributes ;)
            // todo: model page table entry

            uint32_t disc = address & 0xfffff000;
            auto shifted = disc >> 12;
            entry = PageTableEntry {
                    // attributes: supervisor level, read/write, present.
                .access = PageTableAccess {
                        .isPresent = true
                },
                .address = shifted & 0xfffff
            };
            address += 0x1000;
        });

        // todo: model page directory and tables
        auto adr = (unsigned int) firstPageTable.data();
        uint32_t disc = adr & 0xfffff000;
        auto shifted = disc >> 12;
        pageDirectory.front() = {
                .access = PageDirectoryAccess {
                        .isPresent = true,
                        .canWrite = true
                },
                .address = shifted & 0xfffff
        };

        loadPageDirectory(pageDirectory.data());
        enablePaging();
    }

}