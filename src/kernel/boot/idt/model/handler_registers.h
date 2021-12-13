//
// Created by david on 13/12/2021.
//

#ifndef HEPHAISTOS_HANDLER_REGISTERS_H
#define HEPHAISTOS_HANDLER_REGISTERS_H

namespace kernel::boot::idt {

    /**
     *
     */
    struct [[gnu::packed]] Registers {
        const uint32_t edi;
        const uint32_t esi;
        const uint32_t ebp;
        const uint32_t esp;
        const uint32_t ebx;
        const uint32_t edx;
        const uint32_t ecx;
        const uint32_t eax;
    };

    /**
     *
     */
    struct [[gnu::packed]] SegmentRegisters {
        const uint32_t gs;
        const uint32_t fs;
        const uint32_t es;
        const uint32_t ds;
    };

    /**
     *
     */
    struct [[gnu::packed]] CpuRegisters {
        const uint32_t eip;
        const uint32_t cs;
        const uint16_t eflags;
    };
}

#endif //HEPHAISTOS_HANDLER_REGISTERS_H
