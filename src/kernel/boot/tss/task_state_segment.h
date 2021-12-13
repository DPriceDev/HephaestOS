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

#include "kernel/lib/libc/stdint.h"
#include "kernel/boot/gdt/global_descriptor.h"

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
        uint32_t previousTss;

        //
        uint32_t esp0;
        uint32_t ss0;

        //
        uint32_t esp1;
        uint32_t ss1;
        uint32_t esp2;
        uint32_t ss2;
        uint32_t cr3;
        uint32_t eip;
        uint32_t eFlags;
        uint32_t eax;
        uint32_t ecx;
        uint32_t edx;
        uint32_t ebx;
        uint32_t esp;
        uint32_t ebp;
        uint32_t esi;
        uint32_t edi;

        //
        uint32_t es;
        uint32_t cs;
        uint32_t ss;
        uint32_t ds;
        uint32_t fs;
        uint32_t gs;
        uint32_t ldt;
        uint16_t trap;

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
