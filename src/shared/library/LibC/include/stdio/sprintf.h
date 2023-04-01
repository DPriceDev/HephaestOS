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

#ifndef HEPHAEST_OS_KERNEL_LIB_STDIO_SPRINTF_H
#define HEPHAEST_OS_KERNEL_LIB_STDIO_SPRINTF_H

#include <stdint.h>

/**
 * TODO: Comment
 * TODO: Move to strings.h
 * @param buffer
 * @param length
 * @return
 */
char* reverseBuffer(char* buffer, uint32_t length);

/**
 * TODO: Comment
 * TODO: Move to stdlib.h
 * @param value
 * @param buffer
 * @param base
 * @return
 */
char* convertNumberToString(int32_t value, char* buffer, int32_t base);

/**
 *
 * @param str
 * @param format
 * @param ...
 * @return
 */
int sprintf(char* str, const char* format, ...);


#endif// HEPHAEST_OS_KERNEL_LIB_STDIO_SPRINTF_H
