// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

#include "string.h"
#include "stdint.h"

template<typename T>
int Size(T str) {

    uint8_t i(0);

    // count each characters in the characters.
    for (; str[i]; i++) {}

    return i;// return count
}

void* memset(void* pointer, int value, uint32_t length) {
    unsigned char* ptr = static_cast<unsigned char*>(pointer);
    while (length--) { *ptr++ = (unsigned char) value; }
    return pointer;
}

void* memcpy(void* dest, const void* src, size_t n) {
    char* csrc = (char*) src;
    char* cdest = (char*) dest;
    while (n--) { *cdest++ = *csrc++; }
    return dest;
}