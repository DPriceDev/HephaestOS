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
#include "kernel/terminal/TextDisplay.hpp"
#include "kernel/types.h"
#include "memory/memory.hpp"

#define VERSION 1.0

////////////////////////////////////////////////////////////////////////////////
//
//
//
extern "C" void kernelMain()
{   
    TextDisplay td;

     td.clear();

     td.Print("HephaestOS\n");
     td.Print("Version 1.0\n");

    getMemorySize();

    while(1) {

        auto test = ";";
    }
}

////////////////////////////////////////////////////////////////////////////////