//
// Created by david on 24/12/2021.
//

#ifndef HEPHAISTOS_MEMORY_MAP_H
#define HEPHAISTOS_MEMORY_MAP_H

#include "multiboot_info.h"

namespace kernel::boot::grub {

    struct [[gun::packed]] MemoryMap {
        uint32_t size;
    };

    /**
     *
     * @param info
     */
    auto constructMemoryMap(const MultiBootInfo * multiBootInfo) -> void;

}

#endif //HEPHAISTOS_MEMORY_MAP_H
