#include "Terminal.hpp"

#include "kernel/sys.hpp"

kernel::Terminal::Terminal(const kernel::Display &display): mDisplay(display) { }

void kernel::Terminal::print(const char* string, Display::Colour colour) {
    setTextColour(colour);


    while (*string != '\0') {
        if(*string == '\n') {
            addNewLine();
            string++;
            continue;
        }

        if(cursorX == mDisplay.getWidth()) {
            addNewLine();
        }

        auto *position = currentLine->characters + cursorX;
        position->character = *string;
        position->textColour = textColour;
        cursorX++;
        string++;
    }

    updateDisplayBuffer();
    mDisplay.setCursorPosition(cursorX, cursorY);
}

// Function: setTextColour
// desc: This function will set the textColour of the next printed text.
[[maybe_unused]] void kernel::Terminal::setTextColour(const Display::Colour &colour) {
    textColour = colour;
}

// Function: SetCursorPosition
void kernel::Terminal::SetCursorPosition(const uint32_t &x, const uint32_t &y) {
    if(x <= mDisplay.getWidth() && x <= SYS::DISP::SCREEN_BUFFER_SIZE) {
        cursorX = x;
        cursorY = y;
        mDisplay.setCursorPosition(cursorX, cursorY);
    }
}

void kernel::Terminal::clear(Display::Colour colour) {
    mDisplay.clearDisplayBuffer(colour);
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
    mDisplay.setCursorPosition(cursorX, cursorY);
}

void kernel::Terminal::addNewLine() {
    cursorX = 0;
    cursorY++;
    currentLine = lines + cursorY;
}
