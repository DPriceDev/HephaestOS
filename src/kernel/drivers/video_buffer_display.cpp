//
// Created by david on 01/04/2021.
//

#include "video_buffer_display.h"
#include "drivers/io/IO.hpp"

const kernel::uint32_t &kernel::VideoBufferDisplay::getWidth() const {
    return width;
}

const kernel::uint32_t &kernel::VideoBufferDisplay::getHeight() const {
    return height;
}

kernel::uint32_t
kernel::VideoBufferDisplay::setDisplayBuffer(const kernel::Display::Character *character, int length) const {
    auto *videoAddress = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);
    for (unsigned int index = 0; index < screenBufferLength; index += 2) {
        *videoAddress++ = character->character;
        *videoAddress++ = character->textColour;
        character++;

        if (index == length) {
            break;
        }
    }
    return videoAddress - reinterpret_cast<unsigned char *>(address::videoMemoryAddress);
}

void kernel::VideoBufferDisplay::clearDisplayBuffer(Display::Colour colour) const {
    auto *videoAddress = reinterpret_cast<unsigned char *>(address::videoMemoryAddress);
    for (unsigned int index = 0; index < screenBufferLength; index += 2) {
        *videoAddress++ = ' ';
        *videoAddress++ = colour;
    }
}

void kernel::VideoBufferDisplay::setCursorPosition(uint32_t x, uint32_t y) const {
    uint32_t cursorPosition = (y * width) + x;

    outportb(address::videoCursorLowAddress, 0x0F);
    outportb(address::videoCursorHighAddress, cursorPosition);
    outportb(address::videoCursorLowAddress, 0x0E);
    outportb(address::videoCursorHighAddress, cursorPosition >> 8);
}


