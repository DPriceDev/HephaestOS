//
// Created by david on 15/07/2021.
//

#include <kernel/drivers/video_buffer_display.h>
#include <kernel/terminal/Terminal.h>
#include "interrupt_handler.h"

namespace kernel::boot::idt {

    extern "C" void handleInterrupt(InterruptInfo interruptNumber) {
        VideoBufferDisplay display{ };
        auto terminal = Terminal{ display };
        char interruptCode = interruptNumber.interruptCode + 48;
        char pointer[2];
        pointer[0] = interruptCode;
        pointer[1] = '\0';
        terminal.print(pointer);
        terminal.clear(Display::green);
    }
}

