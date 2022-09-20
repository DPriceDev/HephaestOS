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
#include "boot/io.h"
#include <stdio.h>

namespace kernel::boot::idt {

    /**
     *
     */
    extern "C" void handleInterrupt(InterruptInfo interruptInfo) {
        if (interruptInfo.interruptCode == 1) {
            auto input = inputPortByte(0x60);

            std::print("Interrupt!\n");
            std::print("Interrupt code: {}\n", interruptInfo.interruptCode);
        }

        if (interruptInfo.interruptCode != 0 && interruptInfo.interruptCode != 1) {
            std::print("Interrupt! {}\n", interruptInfo.interruptCode);
        }

        sendEoiFlag(interruptInfo.interruptCode);
    }
}