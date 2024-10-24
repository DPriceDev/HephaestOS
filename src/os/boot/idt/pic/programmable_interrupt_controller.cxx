/* Copyright (C) 2023 David Price - All Rights Reserved
 * This file is part of HephaestOS.
 *
 * HephaestOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaestOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
 */

module;

#include <cstdint>

import os.hal.io;

export module os.boot.interrupts.pic;

namespace boot {

    constexpr uint8_t masterPicAddress = 0x20;// IO Address of Master PIC
    constexpr uint8_t slavePicAddress = 0xA0;// IO Address of Slave PIC
    constexpr uint8_t masterPicDataAddress = 0x21;// IO Data Address of Master PIC
    constexpr uint8_t slavePicDataAddress = 0xA1;// IO Data Address of Slave PIC


    constexpr uint8_t ICW1_ICW4 = 0x01; /* ICW4 (not) needed */
    constexpr uint8_t ICW1_SINGLE = 0x02; /* Single (cascade) mode */
    constexpr uint8_t ICW1_INTERVAL4 = 0x04; /* Call address interval 4 (8) */
    constexpr uint8_t ICW1_LEVEL = 0x08; /* Level triggered (edge) mode */
    constexpr uint8_t initializeCommand = 0x10;// Initialize the PIC

    constexpr uint8_t ICW4_8086 = 0x01; /* 8086/88 (MCS-80/85) mode */
    constexpr uint8_t ICW4_AUTO = 0x02; /* Auto (normal) EOI */
    constexpr uint8_t ICW4_BUF_SLAVE = 0x08; /* Buffered mode/slave */
    constexpr uint8_t ICW4_BUF_MASTER = 0x0C; /* Buffered mode/master */
    constexpr uint8_t ICW4_SFNM = 0x10; /* Special fully nested (not) */

    constexpr uint8_t picEoiFlag = 0x20;

    // Maps the overlapping interrupts to after the exceptions.
    export void remapProgrammableInterruptController(uint8_t masterOffset, uint8_t slaveOffset) {
        // initialize pic todo: Comment second command
        hal::writeToPort(masterPicAddress, initializeCommand | ICW1_ICW4);
        hal::waitForIO();
        hal::writeToPort(slavePicAddress, initializeCommand | ICW1_ICW4);
        hal::waitForIO();

        // Set the interrupt offset
        hal::writeToPort(masterPicDataAddress, masterOffset);
        hal::waitForIO();
        hal::writeToPort(slavePicDataAddress, slaveOffset);
        hal::waitForIO();

        // Setup master pic to recognise the slave pic is on IRQ2
        hal::writeToPort(masterPicDataAddress, 4);
        hal::waitForIO();
        // todo: what is a cascade identity?
        hal::writeToPort(slavePicDataAddress, 2);
        hal::waitForIO();

        //
        hal::writeToPort(masterPicDataAddress, ICW4_8086);
        hal::waitForIO();
        hal::writeToPort(slavePicDataAddress, ICW4_8086);
        hal::waitForIO();

        //
        hal::writeToPort(masterPicDataAddress, 0);
        hal::waitForIO();
        hal::writeToPort(slavePicDataAddress, 0);
        hal::waitForIO();
    }

    /**
     *
     * @param interruptCode
     */
    export void sendEoiFlag(uint32_t interruptCode) {
        if (interruptCode >= 8) {
            hal::writeToPort(slavePicAddress, picEoiFlag);
        }

        hal::writeToPort(masterPicAddress, picEoiFlag);
    }
}// namespace boot
