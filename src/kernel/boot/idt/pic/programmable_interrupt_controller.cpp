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

#include "boot/idt/pic/programmable_interrupt_controller.h"

#include "boot/io/io.h"

namespace kernel::boot::idt {

    // Maps the overlapping interrupts to after the exceptions.
    void remapProgrammableInterruptController(
            uint8_t masterOffset,
            uint8_t slaveOffset
    ) {
        // initialize pic todo: Comment second command
        writeToPort(masterPicAddress, initializeCommand | ICW1_ICW4);
        waitForIO();
        writeToPort(slavePicAddress, initializeCommand | ICW1_ICW4);
        waitForIO();

        // Set the interrupt offset
        writeToPort(masterPicDataAddress, masterOffset);
        waitForIO();
        writeToPort(slavePicDataAddress, slaveOffset);
        waitForIO();

        // Setup master pic to recognise the slave pic is on IRQ2
        writeToPort(masterPicDataAddress, 4);
        waitForIO();
        // todo: what is a cascade identity?
        writeToPort(slavePicDataAddress, 2);
        waitForIO();

        //
        writeToPort(masterPicDataAddress, ICW4_8086);
        waitForIO();
        writeToPort(slavePicDataAddress, ICW4_8086);
        waitForIO();

        //
        writeToPort(masterPicDataAddress, 0);
        waitForIO();
        writeToPort(slavePicDataAddress, 0);
        waitForIO();
    }

    /**
     *
     * @param interruptCode
     */
    void sendEoiFlag(uint32_t interruptCode) {
        if(interruptCode >= 8) {
            writeToPort(slavePicAddress, picEoiFlag);
        }

        writeToPort(masterPicAddress, picEoiFlag);
    }
}

