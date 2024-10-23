/* Copyright (C) 2023 David Price - All Rights Reserved
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

module;

#include <array.h>
#include <format.h>

import os.boot.interrupt.registers;

export module os.boot.interrupt.exception;

namespace boot {

    export struct [[gnu::packed]] ExceptionInfo {
        const SegmentRegisters segmentRegisters;
        const Registers registers;
        const uint32_t interruptCode;
        const uint32_t errorCode;
        const CpuRegisters cpuRegisters;
    };

    //
    constexpr uint32_t exceptionTableSize = 32;

    constexpr std::Array<const char *, exceptionTableSize> exceptionDescription {
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

    // handles an exception for the provided exception info
    extern "C" void handleException(ExceptionInfo exceptionInfo) {

        std::print("ERROR: Exception\n!");
        std::print("ERROR: Exception code: {}\n", exceptionInfo.interruptCode);

        const auto* description = exceptionDescription[exceptionInfo.interruptCode];
        std::print(description);

        while (true) {}
    }
}// namespace boot