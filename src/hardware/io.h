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

#ifndef HEPHAIST_OS_DRIVERS_IO_IO_H
#define HEPHAIST_OS_DRIVERS_IO_IO_H

#include "kernel/types.h"
#include "hardware/register_address.h"

namespace kernel {

    inline uint8_t inputPortByte(uint32_t port) {
        uint8_t byte{ 0 };
        asm volatile ("inb %%dx,%%al":"=a" (byte):"d" (port));
        return byte;
    }

    inline void outputPortByte(uint32_t port, uint8_t value) {
        asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
    }


    inline void ioWait() {
        asm volatile( "outb %%al, $0x80" : : "a"(0) );
    }
}

#endif
////////////////////////////////////////////////////////////////////////////////