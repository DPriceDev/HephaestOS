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

#include "idt/pic/programmable_interrupt_controller.h"

#include "io.h"

namespace boot {

    // Maps the overlapping interrupts to after the exceptions.
    void remapProgrammableInterruptController(uint8_t masterOffset, uint8_t slaveOffset) {
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
    void sendEoiFlag(uint32_t interruptCode) {
        if (interruptCode >= 8) {
            hal::writeToPort(slavePicAddress, picEoiFlag);
        }

        hal::writeToPort(masterPicAddress, picEoiFlag);
    }
}// namespace boot
