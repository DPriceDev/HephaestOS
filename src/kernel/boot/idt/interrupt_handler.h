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
        uint32_t edi;
        uint32_t esi;
        uint32_t ebp;
        uint32_t esp;
        uint32_t ebx;
        uint32_t edx;
        uint32_t ecx;
        uint32_t eax;
    } __attribute__((packed));

    struct SegmentRegisters {
        uint32_t gs;
        uint32_t fs;
        uint32_t es;
        uint32_t ds;
    };

    struct CpuRegisters {
        uint32_t eip;
        uint32_t cs;
        uint16_t eflags;
    };

    struct InterruptInfo {
        SegmentRegisters segmentRegisters;
        Registers registers;
        uint32_t interruptCode;
        CpuRegisters cpuRegisters;
    } __attribute__((packed));

    struct ExceptionInfo {
        SegmentRegisters segmentRegisters;
        Registers registers;
        uint32_t interruptCode;
        uint32_t errorCode;
        CpuRegisters cpuRegisters;
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
