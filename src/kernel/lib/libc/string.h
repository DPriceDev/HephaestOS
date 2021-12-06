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

#ifndef SYS_STRING_H
#define SYS_STRING_H

#include "stdint.h"

namespace kernel::lib {

    template<typename T>
    int Size(T str) {

        uint8_t i(0);

        // count each characters in the characters.
        for (; str[i]; i++);

        return i;       // return count
    }

    void* memset(void* pointer, int value, uint32_t length) {
        unsigned char* ptr = static_cast<unsigned char *>(pointer);
        while(length--)
        {
            *ptr++ = (unsigned char) value;
        }
        return pointer;
    }
}

#endif