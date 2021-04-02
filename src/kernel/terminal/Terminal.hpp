////////////////////////////////////////////////////////////////////////////////
// Title:           Text Display Class
// Filename:        Terminal.cpp
// Last Changed:    17/08/19
// Created:         17/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 00:07 17/08/19: Class created with default constructors.
//      - 00:07 17/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#ifndef HEPHAIST_OS_KERNEL_DISPLAY_H
#define HEPHAIST_OS_KERNEL_DISPLAY_H

#include "kernel/drivers/display.h"

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

        void clear(Display::Colour colour = Display::black);

        [[maybe_unused]] void setTextColour(const Display::Colour &colour);

        [[maybe_unused]] void SetCursorPosition(const uint32_t &x, const uint32_t &y);

    private:
        static const uint32_t maxLines{50};
        const Display &mDisplay;
        uint32_t cursorX{0};
        uint32_t cursorY{0};

        Line lines[maxLines];
        Line *currentLine = lines;
        kernel::Display::Character buffer[maxLines * 80];

        Display::Colour textColour{Display::white};

        void addNewLine();

        void updateDisplayBuffer();
    };
}
#endif