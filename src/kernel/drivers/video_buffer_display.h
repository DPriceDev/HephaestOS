//
// Created by david on 01/04/2021.
//

#ifndef HEPHAISTOS_VIDEO_BUFFER_DISPLAY_H
#define HEPHAISTOS_VIDEO_BUFFER_DISPLAY_H

#include "display.h"
#include "kernel/types.h"

namespace kernel {

class VideoBufferDisplay : public Display {
        const uint32_t width{ 80 };
        const uint32_t characterWidth{ width * 2 };
        const uint32_t height{ 25 };
        const uint32_t screenBufferLength{ characterWidth * height };

    public:
        [[nodiscard]] const uint32_t &getWidth() const override;
        [[nodiscard]] const uint32_t & getHeight() const override;

        void clearDisplayBuffer(Display::Colour colour) const override;

        uint32_t setDisplayBuffer(const Character *character, int length) const override;

        // todo: showCursor(boolean shouldShow)
        void setCursorPosition(uint32_t x, uint32_t y) const override;
    };

}

#endif //HEPHAISTOS_VIDEO_BUFFER_DISPLAY_H
