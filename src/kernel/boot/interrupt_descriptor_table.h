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

    struct TypeAttributes {
        uint8_t gateType : 4;
        uint8_t storageSegment : 1;
        uint8_t descriptorLevel : 2;
        uint8_t isPresent : 1;
    };

    struct InterruptDescriptor {
        uint16_t lowerOffset;
        uint16_t selector;
        uint8_t zero;
        TypeAttributes gateType;
        uint16_t higherOffset;
    } __attribute__((packed));

    extern "C" void idtFlush(uint32_t pointer);

    extern "C" int irq0();

    constexpr InterruptDescriptor constructInterruptDescriptor(uint32_t handler) {
        InterruptDescriptor descriptor {
                static_cast<uint16_t>(handler & 0xFFFF),
                0x08,
                0,
                TypeAttributes {
                    14, 0, 1, 1
                },
                static_cast<uint16_t>((handler >> 16) & 0xFFFF)
        };

        return descriptor;
    }

    struct IdtPointer {
        uint16_t size;
        uint32_t pointer;
    } __attribute__((packed));

    extern "C" void irq0_handler(void) {
        VideoBufferDisplay display { };
        auto terminal = kernel::Terminal{display};
        terminal.clear(Display::green);
    }

    InterruptDescriptor interruptDescriptorTable[256];

    const IdtPointer idtPointer = IdtPointer {
            (sizeof(InterruptDescriptor) * 256) - 1,
            (uint32_t) interruptDescriptorTable
    };

    void initializeInterruptDescriptorTable() {
        interruptDescriptorTable[0] = constructInterruptDescriptor((uint32_t)  irq0);
        interruptDescriptorTable[1] = constructInterruptDescriptor((uint32_t)  irq0);
        idtFlush((uint32_t) &idtPointer);
    }
}

#endif //HEPHAISTOS_INTERRUPT_DESCRIPTOR_TABLE_H
