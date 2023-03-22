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
#ifndef HEPHAIST_OS_KERNEL_BOOT_TSS_H
#define HEPHAIST_OS_KERNEL_BOOT_TSS_H

#include <cstdint>
#include "gdt/global_descriptor.h"

namespace kernel::boot::tss {

    extern "C" void loadTaskRegister(gdt::Segment segment, gdt::Privilege privilege);

    // todo: Move this out to a user space class?
    extern "C" void jumpUserMode();

    auto initializeTaskStateSegment(uint32_t stackPointer) -> void;

    auto getTaskStateSegmentDescriptor() -> gdt::GlobalDescriptor;

    /**
     *
     */
    struct [[gnu::packed]] TssEntry {
        uint32_t previousTss = 0;

        //
        uint32_t esp0 = 0;
        uint32_t ss0 = 0;

        //
        uint32_t esp1 = 0;
        uint32_t ss1 = 0;
        uint32_t esp2 = 0;
        uint32_t ss2 = 0;
        uint32_t cr3 = 0;
        uint32_t eip = 0;
        uint32_t eFlags = 0;
        uint32_t eax = 0;
        uint32_t ecx = 0;
        uint32_t edx = 0;
        uint32_t ebx = 0;
        uint32_t esp = 0;
        uint32_t ebp = 0;
        uint32_t esi = 0;
        uint32_t edi = 0;

        //
        uint32_t es = 0;
        uint32_t cs = 0;
        uint32_t ss = 0;
        uint32_t ds = 0;
        uint32_t fs = 0;
        uint32_t gs = 0;
        uint32_t ldt = 0;
        uint16_t trap = 0;

        //
        uint16_t ioMapBase;
    };

    //
    constexpr gdt::Flags tssFlags {
        .available = false,
        .longMode = false,
        .size = gdt::Size::Bit16,
        .granularity = gdt::Granularity::Byte
    };

    //
    constexpr gdt::Access tssEntryAccess {
        .accessed = true,
        .readWritable = false,
        .isConforming = false,
        .isExecutable = true,
        .descriptorType = gdt::DescriptorType::System,
        .privilege = gdt::Privilege::Kernel,
        .present = true
    };
}

#endif // HEPHAIST_OS_KERNEL_BOOT_TSS_H
