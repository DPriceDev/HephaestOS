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

#include "Terminal.h"

kernel::Terminal::Terminal(const kernel::Display &display): mDisplay(display), cursor(mDisplay.getCursorPosition()) {
    mDisplay.showCursor();
}

void kernel::Terminal::print(const char* string, Display::Colour colour) {
    setTextColour(colour);

    while (*string != '\0') {
        if(*string == '\n') {
            addNewLine();
            string++;
            continue;
        }

        if(cursor.x == mDisplay.getWidth()) {
            addNewLine();
        }

        auto *position = currentLine->characters + cursor.x;
        position->character = *string;
        position->textColour = textColour;
        cursor.x++;
        string++;
    }

    updateDisplayBuffer();
    mDisplay.setCursorPosition(cursor.x, cursor.y);
}

// Function: setTextColour
// desc: This function will set the textColour of the next printed text.
[[maybe_unused]] void kernel::Terminal::setTextColour(const Display::Colour &colour) {
    textColour = colour;
}

// Function: SetCursorPosition
void kernel::Terminal::SetCursorPosition(const uint32_t &x, const uint32_t &y) {
    if(x <= mDisplay.getWidth()) {
        cursor.x = x;
        cursor.y = y;
        mDisplay.setCursorPosition(cursor.x, cursor.y);
    }
}

void kernel::Terminal::clear(Display::Colour backgroundColour) {
    mDisplay.clearDisplayBuffer(textColour, backgroundColour);
    cursor.x = 0;
    cursor.y = 0;
    mDisplay.setCursorPosition(0, 0);
}

void kernel::Terminal::updateDisplayBuffer() {
    auto index{ 0 };

    for (auto & line : lines) {
        for (auto & character : line.characters) {
            buffer[index] = character;
            ++index;
        }
    }
    mDisplay.setDisplayBuffer(buffer, index);
}

void kernel::Terminal::println(const char *string, kernel::Display::Colour colour) {
    print(string, colour);
    addNewLine();
    updateDisplayBuffer();
    mDisplay.setCursorPosition(cursor.x, cursor.y);
}

void kernel::Terminal::addNewLine() {
    cursor.x = 0;
    cursor.y++;
    currentLine = lines + cursor.y;
}
