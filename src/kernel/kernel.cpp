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
#include "kernel/types.h"
#include "kernel/boot/tss/tss.h"

namespace kernel {

    extern "C" void testUserFunction() {
        static const VideoBufferDisplay display { };
        auto terminal = kernel::Terminal{display};

        terminal.println("HephaistOS");
        terminal.println("Version 1.0", kernel::Display::cyan);

        auto test = 0 / 0;
        auto sdfsdf = test * 2;

        while(true) {

        }
    };


    // todo: Should this live in a config file somewhere?
    constexpr uint32_t majorVersion = 1;
    constexpr uint32_t minorVersion = 0;
    constexpr uint32_t fixVersion = 0;

    extern "C" void kernelMain() {

        // todo: Extract out all terminal code to user space

//        while(true) {
//
//        }

        // todo: Init Timer Task? (or in init.cpp)

        // todo: Init IPC Task

        // todo: Init memory manager Task

        // todo: Init process table task

        // todo: Init basic scheduler Task?

        // todo: Load Ram Disk

        // todo: Start Root Process

        // todo: Switch to Ring 3
        boot::tss::jumpUserMode();
    }
}