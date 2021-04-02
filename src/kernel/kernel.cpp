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
#include "kernel/boot/multiboot_info.h"
#include "kernel/types.h"

#define VERSION 1.0

namespace kernel {

/**
 * Kernel Entry Point
 */
    extern "C" [[noreturn]] void kernelMain() {
        auto display = kernel::VideoBufferDisplay();
        auto terminal = kernel::Terminal{display};

        terminal.clear();

        terminal.println("HephaestOS");
        terminal.println("Version 1.0", kernel::Display::cyan);


        while (true) {

        }
    }
}