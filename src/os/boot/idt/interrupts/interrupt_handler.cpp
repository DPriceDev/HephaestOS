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

#include "interrupt_handler.h"
#include "idt/pic/programmable_interrupt_controller.h"

#include "../hal/io/io.h"
#include <format.h>

namespace boot {


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