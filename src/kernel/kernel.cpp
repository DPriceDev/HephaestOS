////////////////////////////////////////////////////////////////////////////////
// Title:           kernel
// Filename:        kernel.cpp
// Last Changed:    16/08/19
// Created:         16/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 23:30 16/08/19: KernelMain and printf added.
//      - 23:30 16/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#include <kernel/drivers/video_buffer_display.h>
#include "kernel/terminal/Terminal.hpp"
#include "kernel/types.h"
#include "memory/memory.hpp"

#define VERSION 1.0

////////////////////////////////////////////////////////////////////////////////
//
//
//
extern "C" [[noreturn]] void kernelMain()
{
    auto display = kernel::VideoBufferDisplay();
    auto terminal = kernel::Terminal{ display };

    terminal.clear();

    terminal.println("HephaestOS");
    terminal.println("Version 1.0", kernel::Display::cyan);

    while(true) {

    }
}

////////////////////////////////////////////////////////////////////////////////