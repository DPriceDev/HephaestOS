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

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H

#include <kernel/types.h>

namespace kernel::boot::idt {

    struct Registers {
        const uint32_t edi;
        const uint32_t esi;
        const uint32_t ebp;
        const uint32_t esp;
        const uint32_t ebx;
        const uint32_t edx;
        const uint32_t ecx;
        const uint32_t eax;
    } __attribute__((packed));

    struct SegmentRegisters {
        const uint32_t gs;
        const uint32_t fs;
        const uint32_t es;
        const uint32_t ds;
    };

    struct CpuRegisters {
        const uint32_t eip;
        const uint32_t cs;
        const uint16_t eflags;
    };

    struct InterruptInfo {
        const SegmentRegisters segmentRegisters;
        const Registers registers;
        const uint32_t interruptCode;
        const CpuRegisters cpuRegisters;
    } __attribute__((packed));

    struct ExceptionInfo {
        const SegmentRegisters segmentRegisters;
        const Registers registers;
        const uint32_t interruptCode;
        const uint32_t errorCode;
        const CpuRegisters cpuRegisters;
    } __attribute__((packed));

    constexpr char * exceptionDescription[] {
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

    extern "C" void handleInterrupt(InterruptInfo interruptInfo);

    extern "C" [[noreturn]] void handleException(ExceptionInfo exceptionInfo);
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H
