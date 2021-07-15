//
// Created by david on 15/07/2021.
//

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H

namespace kernel::boot::idt {

    extern "C" void irq0_handler(void);
}

#endif // HEPHAIST_OS_KERNEL_BOOT_IDT_INTERRUPT_HANDLER_H
