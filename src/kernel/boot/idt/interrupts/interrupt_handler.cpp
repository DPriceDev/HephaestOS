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

#include "interrupt_handler.h"
#include "boot/idt/pic/programmable_interrupt_controller.h"

#include <format.h>
#include "boot/io/io.h"

namespace kernel::boot::idt {


    void handleKeyboardPress(InterruptInfo interruptInfo) {
        auto input = readFromPort(0x60);

        std::print("Interrupt code: {}\n", interruptInfo.interruptCode);
        std::print("Key Pressed: {}\n", input);
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
                std::print("Interrupt code: {}\n", interruptInfo.interruptCode);
                break;
        }

        sendEoiFlag(interruptInfo.interruptCode);
    }

}