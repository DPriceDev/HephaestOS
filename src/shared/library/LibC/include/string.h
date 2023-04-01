// Copyright (C) 2023 David Price - All Rights Reserved
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

#ifndef HEPHAEST_OS_USER_LIB_C_STRING_H
#define HEPHAEST_OS_USER_LIB_C_STRING_H

#include "stdint.h"

/**
 * size_t is the maximum size an object could be.
 */
typedef long unsigned int size_t;

/**
 * Stubbed strlen.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
size_t strlen(const char* str);

/**
 * Stubbed memset.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
void* memset(void* pointer, int value, uint32_t length);

/**
 * Stubbed memcpy.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
void* memcpy(void* dest, const void* src, size_t n);

/**
 * Stubbed strcpy.
 * Stubbed to allow GCC to compile, just needs to exist at this point without an implementation.
 */
char* strcpy(char* dest, const char* src);

#endif// HEPHAEST_OS_USER_LIB_C_STRING_H