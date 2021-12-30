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

#ifndef HEPHAIST_OS_KERNEL_DRIVERS_DISPLAY_H
#define HEPHAIST_OS_KERNEL_DRIVERS_DISPLAY_H

#include <stdint.h>

namespace kernel {

// todo: implement memory to provide delete for destructor?
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
    class Display {
    public:
        enum Colour {
            black,
            blue,
            green,
            cyan,
            red,
            purple,
            brown,
            gray,
            darkGray,
            lightBlue,
            lightGreen,
            lightCyan,
            lightRed,
            lightPurple,
            yellow,
            white
        };

        struct Character {
            int8_t character;
            int8_t textColour = Display::white;
        } __attribute__((aligned(2)));

        struct Cursor {
            uint32_t x;
            uint32_t y;
        } __attribute__((aligned(8)));

        [[nodiscard]] virtual const uint32_t &getWidth() const = 0;
        [[nodiscard]] virtual const uint32_t &getHeight() const = 0;

        virtual void clearDisplayBuffer(Display::Colour textColour, Display::Colour backgroundColour) const = 0;

        virtual uint32_t setDisplayBuffer(const Character* character, uint32_t length) const = 0;

        virtual uint32_t setDisplayBuffer(const Character *character, uint32_t length, uint32_t x, uint32_t y) const = 0;

        virtual void showCursor() const = 0;
        virtual void hideCursor() const = 0;

        [[nodiscard]] virtual Cursor getCursorPosition() const = 0;

        virtual void setCursorPosition(uint32_t x, uint32_t y) const = 0;
    };
#pragma GCC diagnostic pop

}
#endif //HEPHAISTOS_DISPLAY_H
