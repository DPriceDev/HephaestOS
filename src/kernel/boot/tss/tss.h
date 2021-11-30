//
// Created by david on 30/11/2021.
//

#ifndef HEPHAISTOS_TSS_H
#define HEPHAISTOS_TSS_H

#include "kernel/types.h"

namespace kernel::boot::tss {

    extern "C" void flushTss();

    extern "C" void jumpUserMode();

    struct TssEntry {
        uint32_t previousTss; // The previous TSS - with hardware task switching these form a kind of backward linked list.
        uint32_t esp0;     // The stack pointer to load when changing to kernel mode.
        uint32_t ss0;      // The stack segment to load when changing to kernel mode.
        // Everything below here is unused.
        uint32_t esp1; // esp and ss 1 and 2 would be used when switching to rings 1 or 2.
        uint32_t ss1;
        uint32_t esp2;
        uint32_t ss2;
        uint32_t cr3;
        uint32_t eip;
        uint32_t eFlags;
        uint32_t eax;
        uint32_t ecx;
        uint32_t edx;
        uint32_t ebx;
        uint32_t esp;
        uint32_t ebp;
        uint32_t esi;
        uint32_t edi;
        uint32_t es;
        uint32_t cs;
        uint32_t ss;
        uint32_t ds;
        uint32_t fs;
        uint32_t gs;
        uint32_t ldt;
        uint16_t trap;
        uint16_t ioMapBase;
    } __attribute__((packed));
}

#endif //HEPHAISTOS_TSS_H
