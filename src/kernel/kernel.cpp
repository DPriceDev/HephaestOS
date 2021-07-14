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

#include <kernel/drivers/video_buffer_display.h>
#include "kernel/terminal/Terminal.h"
#include "kernel/memory/memory.h"
#include "hardware/io.h"

#define VERSION 1.0

namespace kernel {

    extern "C" [[noreturn]] void kernelMain() {
        static const VideoBufferDisplay display { };
        auto terminal = kernel::Terminal{display};

        /* mask interrupts */
        //outputPortByte(0x21 , 0xff);
        //outputPortByte(0xA1 , 0xff);
//
        //outputPortByte(0x21,0xfd);
        //outputPortByte(0xa1,0xff);

        terminal.println("HephaestOS");
        terminal.println("Version 1.0", kernel::Display::cyan);

        while(true) {

        }
    }
}