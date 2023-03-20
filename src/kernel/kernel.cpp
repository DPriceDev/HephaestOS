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

#include <stdoffset.h>
#include <format.h>

namespace kernel {

    // todo: Should this live in a config file somewhere?
    constexpr uint32_t majorVersion = 1;
    constexpr uint32_t minorVersion = 0;
    constexpr uint32_t fixVersion = 0;

//    static const SerialPortConnection connection { SerialPort::COM1 };
//
//    void initializeSerialPort() {
//        if (connection.open()) {
//            std::KernelFormatOutput::getInstance().setStandardOutputIterator(
//                std::StandardOutputIterator {
//                    &connection,
//                    [] (const void* pointer) { },
//                    [] (const void* pointer, char character) {
//                        static_cast<const SerialPortConnection*>(pointer)->write(character);
//                    },
//                    [] (const void* pointer) { },
//                }
//            );
//        }
//    }

    extern "C" [[maybe_unused]] void kernelMain() {

     //   std::print("HephaistOS\n");
      //  std::print("Version 1.0\n");

        // TODO: Register timer with timer interrupt

        // todo: Init Timer? (or in init.LibCpp)

        // todo: Init IPC?

        // todo: Init memory manager? basic manager, user space memory manager

        // todo: Init page manager? Basic pages, linked to memory manager? proxy?

        // todo: Init process table

        // Something something Syscalls something?

        // todo: Load Ram Disk

        // Register ram disk root process

        // todo: Jump to ram disk main in ring 3

        //boot::tss::jumpUserMode();

        // todo: Unload boot code
        // TODO: Unload this bit of kernel code?

        // todo: Remove and add an error message here, should never get here?
        while(true) {
            /* Endless Loop */
        }

        std::print("ERROR: Reached end of kernel code!");
    }
}