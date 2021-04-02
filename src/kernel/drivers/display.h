//
// Created by david on 01/04/2021.
//

#ifndef HEPHAIST_OS_KERNEL_DRIVERS_DISPLAY_H
#define HEPHAIST_OS_KERNEL_DRIVERS_DISPLAY_H

#include "kernel/types.h"

namespace kernel {

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
            uint8_t character;
            uint8_t textColour;
        } __attribute__((aligned(2)));

        [[nodiscard]] virtual const uint32_t &getWidth() const = 0;
        [[nodiscard]] virtual const uint32_t &getHeight() const = 0;

        virtual void clearDisplayBuffer(Display::Colour colour) const = 0;

        virtual uint32_t setDisplayBuffer(const Character* character, int length) const = 0;

        virtual void setCursorPosition(uint32_t x, uint32_t y) const = 0;
    };

}
#endif //HEPHAISTOS_DISPLAY_H
