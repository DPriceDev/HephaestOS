//
// Created by david on 03/04/2021.
//

#ifndef HEPHAIST_OS_INTERRUPT_DESCRIPTOR_TABLE_H
#define HEPHAIST_OS_INTERRUPT_DESCRIPTOR_TABLE_H

#include <kernel/drivers/video_buffer_display.h>
#include <kernel/terminal/Terminal.h>
#include "kernel/types.h"
#include "hardware/io.h"

namespace kernel::idt {

    enum class GateType {
        task = 5,
        interrupt = 6,
        trap = 7
    };

    struct InterruptDescriptor {
        uint16_t lowerOffset;
        uint16_t selector;
        uint8_t zero;
        GateType gateType : 4;
        uint16_t higherOffset;
    } __attribute__((packed, aligned(16)));

    extern "C" void setInterruptDescriptorTable(uint32_t* tablePointer);

    extern "C" int irq0();

    unsigned long irq0_address;


    extern "C" void irq0_handler(void) {
        VideoBufferDisplay display { };
        auto terminal = kernel::Terminal{display};
        terminal.clear(Display::green);
        //terminal.println("sdfsadfds");
        //int test = 0;
        //test += 2;
        //outputPortByte(0x20, 0x20); //EOI
    }

    InterruptDescriptor constructInterruptDescriptor(uint32_t handler) {
//        auto as = reinterpret_cast<void *>(interruptHandler);
//        auto ass = reinterpret_cast<uint32_t>(as);

        auto test = InterruptDescriptor {
                static_cast<uint16_t>(handler & 0xFFFF),
                0x08,
                0,
                GateType::interrupt,
                static_cast<uint16_t>((handler & 0xFFFF0000) >> 16)
        };

        return test;
    }

    void initializeInterruptDescriptorTable() {

        /*     Ports
        *	 PIC1	PIC2
        *Command 0x20	0xA0
        *Data	 0x21	0xA1
        */

        /* ICW1 - begin initialization */
        outputPortByte(0x20 , 0x11);
        outputPortByte(0xA0 , 0x11);

        /* ICW2 - remap offset address of IDT */
        /*
        * In x86 protected mode, we have to remap the PICs beyond 0x20 because
        * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
        */
        outputPortByte(0x21 , 0x20);
        outputPortByte(0xA1 , 0x28);

        /* ICW3 - setup cascading */
        outputPortByte(0x21 , 0x00);
        outputPortByte(0xA1 , 0x00);

        /* ICW4 - environment info */
        outputPortByte(0x21 , 0x01);
        outputPortByte(0xA1 , 0x01);
        /* Initialization finished */

        InterruptDescriptor t[] = {
                constructInterruptDescriptor(irq0_address),
                constructInterruptDescriptor(irq0_address),
                constructInterruptDescriptor(irq0_address),
        };

        auto *ptr = &t;
        auto idt_address = reinterpret_cast<uint32_t>(ptr);
        uint32_t idt_ptr[2];
        idt_ptr[0] = (sizeof(InterruptDescriptor) * 256) + ((idt_address & 0xffff) << 16);
        idt_ptr[1] = idt_address >> 16 ;

        setInterruptDescriptorTable(idt_ptr);
    }
}

#endif //HEPHAISTOS_INTERRUPT_DESCRIPTOR_TABLE_H
