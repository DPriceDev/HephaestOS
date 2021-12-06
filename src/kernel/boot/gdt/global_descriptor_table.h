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

#ifndef HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H
#define HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H

#include <kernel/lib/libc/stdint.h>
#include "global_descriptor.h"

namespace kernel::boot::gdt {

    constexpr uint32_t MaximumMemoryLimit = 0xFFFFF;

    enum class Segment {
        Null = 0x0,
        KernelCode = 0x8,
        KernelData = 0x10,
        UserSpaceCode = 0x18,
        UserSpaceData = 0x20,
        tss = 0x28
    };

    struct [[gnu::packed]] GdtPointer {
        uint16_t size;
        const GlobalDescriptor* address;
    };

    void initializeGlobalDescriptorTable(uint32_t stackPointer);

    extern "C" void loadGdtTable(const GdtPointer* pointer);
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_TABLE_H
