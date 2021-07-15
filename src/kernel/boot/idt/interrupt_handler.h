//
// Created by david on 15/07/2021.
//

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H

#include <kernel/types.h>

namespace kernel::boot::idt {

    struct InterruptInfo {
        uint32_t edi;
        uint32_t esi;
        uint32_t ebp;
        uint32_t esp;
        uint32_t ebx;
        uint32_t edx;
        uint32_t ecx;
        uint32_t eax;
        uint32_t interruptCode;
    } __attribute__((packed));

    extern "C" void handleInterrupt(InterruptInfo interruptNumber);
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H
