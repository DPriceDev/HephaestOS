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

#ifndef HEPHAIST_OS_DRIVERS_VIDEO_BUFFER_DISPLAY_H
#define HEPHAIST_OS_DRIVERS_VIDEO_BUFFER_DISPLAY_H

#include <stdint.h>

#include "display.h"
#include "register_address.h"

namespace kernel {

// todo: implement memory to provide delete for destructor?
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
    class VideoBufferDisplay : public Display {
        const uint8_t cursorStart = 13;
        const uint8_t cursorEnd = 15;

        const uint32_t width{80};
        const uint32_t characterWidth{width * 2};
        const uint32_t height{25};
        const uint32_t screenBufferLength{characterWidth * height};

    public:

        [[nodiscard]] const uint32_t &getWidth() const override;

        [[nodiscard]] const uint32_t &getHeight() const override;

        void clearDisplayBuffer(Display::Colour textColour, Display::Colour backgroundColour) const override;

        uint32_t setDisplayBuffer(const Character *character, uint32_t length, uint32_t x, uint32_t y) const override;

        uint32_t setDisplayBuffer(const Character *character, uint32_t length) const override;

        void showCursor() const override;

        void hideCursor() const override;

        void setCursorPosition(uint32_t x, uint32_t y) const override;

        [[nodiscard]] Cursor getCursorPosition() const override;
    };

#pragma GCC diagnostic pop
}

#endif // HEPHAIST_OS_DRIVERS_VIDEO_BUFFER_DISPLAY_H
