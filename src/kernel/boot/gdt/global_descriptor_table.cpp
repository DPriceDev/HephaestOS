//
// Created by david on 15/07/2021.
//

#include "global_descriptor_table.h"

namespace kernel::boot::gdt {

    void initializeGlobalDescriptorTable() {
        loadGdtTable((uint32_t) &gdtPointer);
    }
}