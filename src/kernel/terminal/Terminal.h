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

#ifndef HEPHAIST_OS_KERNEL_TERMINAL_TERMINAL_H
#define HEPHAIST_OS_KERNEL_TERMINAL_TERMINAL_H

#include "drivers/display.h"

namespace kernel {

    class Terminal {
    public:
        struct Line {
            bool isSubmitted;
            Display::Character characters[80];
        };

        explicit Terminal(const Display &display);

        void print(const char *string, Display::Colour colour = Display::white);

        void println(const char *string, Display::Colour colour = Display::white);

        void clear(Display::Colour backgroundColour = Display::black);

        [[maybe_unused]] void setTextColour(const Display::Colour &colour);

        [[maybe_unused]] void SetCursorPosition(const uint32_t &x, const uint32_t &y);

    private:
        static const uint32_t maxLines{50};
        const Display &mDisplay;
        Display::Cursor cursor;

        Line lines[maxLines];
        Line *currentLine = lines;
        kernel::Display::Character buffer[maxLines * 80];

        Display::Colour textColour{Display::white};

        void addNewLine();

        void updateDisplayBuffer();
    };
}
#endif // HEPHAIST_OS_KERNEL_TERMINAL_TERMINAL_H