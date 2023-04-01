/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaestOS.
 *
 * HephaestOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaestOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef HEPHAEST_OS_KERNEL_BOOT_TSS_H
#define HEPHAEST_OS_KERNEL_BOOT_TSS_H

#include "gdt/global_descriptor.h"
#include <cstdint>

namespace boot {

    extern "C" void loadTaskRegister(Segment segment, Privilege privilege);

    // todo: Move this out to a user space class?
    extern "C" void jumpUserMode();

    auto initializeTaskStateSegment(uint32_t stackPointer) -> void;

    auto getTaskStateSegmentDescriptor() -> GlobalDescriptor;

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
    constexpr Flags tssFlags { .available = false,
                               .longMode = false,
                               .size = Size::Bit16,
                               .granularity = Granularity::Byte };

    //
    constexpr Access tssEntryAccess { .accessed = true,
                                      .readWritable = false,
                                      .isConforming = false,
                                      .isExecutable = true,
                                      .descriptorType = DescriptorType::System,
                                      .privilege = Privilege::Kernel,
                                      .present = true };
}// namespace boot

#endif// HEPHAEST_OS_KERNEL_BOOT_TSS_H
