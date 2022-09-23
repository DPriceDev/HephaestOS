/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstdint>
#include <format.h>

#include "gdt/global_descriptor_table.h"
#include "idt/interrupt_descriptor_table.h"
#include "boot/paging/paging.h"
#include "boot/grub/multiboot_info.h"
#include "boot/idt/pic/programmable_interrupt_controller.h"
#include "boot/tss/task_state_segment.h"
#include "boot/grub/memory_map.h"
#include "boot/serial/serial_port.h"

namespace kernel::boot {

    constexpr uint8_t interruptRequestOffset = 32;

    static const SerialPortConnection connection { SerialPort::COM1 };

    extern "C" void init(MultiBootInfo* info, uint32_t /* magic */, uint32_t stackPointer) {

        if (connection.open()) {
            std::KernelFormatOutput::getInstance().setStandardOutputIterator(
                std::StandardOutputIterator {
                    &connection,
                    [] (const void* pointer) { },
                    [] (const void* pointer, char character) {
                        static_cast<const SerialPortConnection*>(pointer)->write(character);
                    },
                    [] (const void* pointer) { },
                }
            );
        }

        std::print("System init\n");

        // todo: move kernel to higher half?
        paging::setupPaging();
        std::print("Paging has been turned on\n");

        // Construct memory map from grub multiboot information passed from grub
        grub::constructMemoryMap(info);

        auto tssDescriptor = tss::getTaskStateSegmentDescriptor();
        gdt::initializeGlobalDescriptorTable(tssDescriptor);
        std::print("Global Descriptor table initialized\n");

        //
        tss::initializeTaskStateSegment(stackPointer);
        std::print("Task State Segment initialized\n");

        //
        idt::initializeInterruptDescriptorTable();
        std::print("Interrupt Descriptor table initialized\n");

        // todo: may need to be moved to init protected method?
        //
        idt::remapProgrammableInterruptController(
            interruptRequestOffset,
            interruptRequestOffset + 8
        );
        std::print("Interrupts remapped\n");



        // Load Kernel Module
    }
}