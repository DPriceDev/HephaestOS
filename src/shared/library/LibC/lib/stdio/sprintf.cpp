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

#include "stdio/sprintf.h"

char* reverseBuffer(char* buffer, uint32_t length) {
    for (uint32_t index = 0; index < length / 2; ++index) {
        char character = buffer[index];
        buffer[index] = buffer[length - index - 1];
        buffer[length - index - 1] = character;
    }
    return buffer;
}

/**
 * TODO: Comment
 * TODO: Move to stdlib.h
 * @param value
 * @param buffer
 * @param base
 * @return
 */
char* convertNumberToString(int32_t value, char* buffer, int32_t base) {
    char* bufferStart = buffer;
    auto shouldAddMinus = value < 0 && base == 10;
    if (shouldAddMinus) {
        value *= -1;
    }

    do {
        const auto number = value % base;
        *buffer = static_cast<char>(number + 48);
        ++buffer;
        value /= base;
    } while (value);

    if (shouldAddMinus) {
        *buffer = '-';
        ++buffer;
    }

    reverseBuffer(bufferStart, static_cast<uint32_t>(buffer - bufferStart));
    return buffer;
}


int sprintf(char* str, const char* format, ...) {
    // todo
    return 0;
}