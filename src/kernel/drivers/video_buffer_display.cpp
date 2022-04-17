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

#include <cstdint>

#include "video_buffer_display.h"
#include "boot/io.h"

constexpr uint16_t eightBitOffset = 8;

const uint32_t& kernel::VideoBufferDisplay::getWidth() const {
    return width;
}

const uint32_t &kernel::VideoBufferDisplay::getHeight() const {
    return height;
}

uint32_t kernel::VideoBufferDisplay::setDisplayBuffer(const Display::Character *character, uint32_t length) const {
    auto *videoPointer = reinterpret_cast<char *>(virtualVideoAddress);
    unsigned int index = 0;
    for (; index < screenBufferLength; index += 2) {
        videoPointer[index] = character->character;
        videoPointer[index + 1] = character->textColour;
        character++;

        if (index == length) {
            break;
        }
    }
    return index / 2;
}

uint32_t kernel::VideoBufferDisplay::setDisplayBuffer(const Display::Character *character,
                                                              uint32_t length,
                                                              uint32_t x,
                                                              uint32_t y) const {
    auto *videoPointer = reinterpret_cast<char *>(virtualVideoAddress);
    uint32_t index = 0;
    uint32_t offset = (y * characterWidth) + (x * 2);
    for (; index < screenBufferLength ; index += 2) {
        videoPointer[index + offset] = character->character;
        videoPointer[index + offset + 1] = character->textColour;
        character++;

        if (index >= length) {
            break;
        }
    }
    return index / 2;
}

void
kernel::VideoBufferDisplay::clearDisplayBuffer(Display::Colour textColour, Display::Colour backgroundColour) const {
    auto *videoPointer = reinterpret_cast<char *>(virtualVideoAddress);
    for (unsigned int index = 0; index < screenBufferLength; index += 2) {
        videoPointer[index] = ' ';
        videoPointer[index + 1] = static_cast<char>(textColour | backgroundColour << 4);
    }
}

void kernel::VideoBufferDisplay::setCursorPosition(uint32_t x, uint32_t y) const {
    uint32_t cursorPosition = (y * width) + x;

    outputPortByte(virtualLowCursorAddress, 0x0F);
    outputPortByte(virtualHighCursorAddress, static_cast<unsigned char>(cursorPosition));
    outputPortByte(virtualLowCursorAddress, 0x0E);
    outputPortByte(virtualHighCursorAddress, static_cast<unsigned char>(cursorPosition >> eightBitOffset));
}

void kernel::VideoBufferDisplay::showCursor() const {
    outputPortByte(virtualLowCursorAddress, 0x0A);
    outputPortByte(virtualHighCursorAddress, (inputPortByte(virtualHighCursorAddress) & 0xC0) | cursorStart);
    outputPortByte(virtualLowCursorAddress, 0x0B);
    outputPortByte(virtualHighCursorAddress, (inputPortByte(virtualHighCursorAddress) & 0xE0) | cursorEnd);
}

void kernel::VideoBufferDisplay::hideCursor() const {
    outputPortByte(virtualLowCursorAddress, 0x0A);
    outputPortByte(virtualHighCursorAddress, 0x20);
}

kernel::Display::Cursor kernel::VideoBufferDisplay::getCursorPosition() const {
    outputPortByte(virtualLowCursorAddress, 0x0F);
    uint16_t position = inputPortByte(virtualHighCursorAddress);

    outputPortByte(virtualLowCursorAddress, 0x0E);
    auto currentHighCursor = inputPortByte(virtualHighCursorAddress);
    position += static_cast<uint16_t>(currentHighCursor << eightBitOffset);

    auto x = position % width;
    auto y = position / width;

    return Display::Cursor{x, y};
}