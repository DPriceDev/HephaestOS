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

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_HANDLER_REGISTERS_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_HANDLER_REGISTERS_H

namespace kernel::boot::idt {

    /**
     *
     */
    struct [[gnu::packed]] Registers {
        const uint32_t edi;
        const uint32_t esi;
        const uint32_t ebp;
        const uint32_t esp;
        const uint32_t ebx;
        const uint32_t edx;
        const uint32_t ecx;
        const uint32_t eax;
    };

    /**
     *
     */
    struct [[gnu::packed]] SegmentRegisters {
        const uint32_t gs;
        const uint32_t fs;
        const uint32_t es;
        const uint32_t ds;
    };

    /**
     *
     */
    struct [[gnu::packed]] CpuRegisters {
        const uint32_t eip;
        const uint32_t cs;
        const uint16_t eflags;
    };
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_HANDLER_REGISTERS_H
