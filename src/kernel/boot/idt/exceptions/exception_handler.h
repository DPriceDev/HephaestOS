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

#ifndef HEPHAISTOS_EXCEPTION_HANDLER_H
#define HEPHAISTOS_EXCEPTION_HANDLER_H

#include <kernel/lib/libc/stdint.h>
#include <kernel/lib/libc/array.h>

#include "kernel/boot/idt/model/handler_registers.h"

namespace kernel::boot::idt {

    /**
     *
     */
    struct [[gnu::packed]] ExceptionInfo {
        const SegmentRegisters segmentRegisters;
        const Registers registers;
        const uint32_t interruptCode;
        const uint32_t errorCode;
        const CpuRegisters cpuRegisters;
    };

    //
    constexpr uint32_t exceptionTableSize = 32;

    //
    constexpr Array<const char *, exceptionTableSize> exceptionDescription {
            "Division By Zero",
            "Debug",
            "Non Maskable Interrupt",
            "Breakpoint",
            "Into Detected Overflow",
            "Out of Bounds",
            "Invalid Opcode",
            "No Coprocessor",
            "Double Fault",
            "Coprocessor Segment Overrun",
            "Bad TSS",
            "Segment Not Present",
            "Stack Fault",
            "General Protection Fault",
            "Page Fault",
            "Unknown Interrupt",
            "Coprocessor Fault",
            "Alignment Check",
            "Machine Check",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved",
            "Reserved"
    };

    /**
     *
     */
    extern "C" [[noreturn]] void handleException(ExceptionInfo exceptionInfo);
}

#endif //HEPHAISTOS_EXCEPTION_HANDLER_H
