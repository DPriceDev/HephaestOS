//
// Created by david on 15/07/2021.
//

#include <kernel/drivers/video_buffer_display.h>
#include <kernel/terminal/Terminal.h>
#include "interrupt_handler.h"

namespace kernel::idt {

    extern "C" void irq0_handler(void) {
        VideoBufferDisplay display{};
        auto terminal = Terminal{ display };
        terminal.clear(Display::green);
    }
}

