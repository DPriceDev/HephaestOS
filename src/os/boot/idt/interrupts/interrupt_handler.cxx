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

#include <format.h>

import os.boot.interrupt.registers;
import os.boot.interrupts.pic;
import os.hal.io;

export module os.boot.interrupt.handler;

namespace boot {

    /**
    *
    */
    struct [[gnu::packed]] InterruptInfo {
        const SegmentRegisters segmentRegisters;
        const Registers registers;
        const uint32_t interruptCode;
        const CpuRegisters cpuRegisters;
    };


    void handleKeyboardPress(InterruptInfo interruptInfo) {
        auto input = hal::readFromPort(0x60);

        std::print("INFO: Interrupt code: {}\n", interruptInfo.interruptCode);
        std::print("INFO: Key Pressed: {}\n", input);
    }

    /**
     *
     */
    extern "C" void handleInterrupt(InterruptInfo interruptInfo) {
        switch (interruptInfo.interruptCode) {
            case 0:
                break;
            case 1:
                handleKeyboardPress(interruptInfo);
                break;
            default:
                std::print("INFO: Interrupt code: {}\n", interruptInfo.interruptCode);
                break;
        }

        sendEoiFlag(interruptInfo.interruptCode);
    }

}// namespace boot