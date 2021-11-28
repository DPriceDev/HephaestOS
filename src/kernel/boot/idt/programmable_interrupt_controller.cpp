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

#include "programmable_interrupt_controller.h"

#include "hardware/io.h"

namespace kernel::boot::idt {

    // Maps the overlapping interrupts to after the exceptions.
    void remapProgrammableInterruptController(
            uint8_t masterOffset,
            uint8_t slaveOffset
    ) {
        // initialize pic todo: Comment second command
        outputPortByte(masterPicAddress, initializeCommand | ICW1_ICW4);
        ioWait();
        outputPortByte(slavePicAddress, initializeCommand | ICW1_ICW4);
        ioWait();

        // Set the interrupt offset
        outputPortByte(masterPicDataAddress, masterOffset);
        ioWait();
        outputPortByte(slavePicDataAddress, slaveOffset);
        ioWait();

        // Setup master pic to recognise the slave pic is on IRQ2
        outputPortByte(masterPicDataAddress, 4);
        ioWait();
        // todo: what is a cascade identity?
        outputPortByte(slavePicDataAddress, 2);
        ioWait();

        //
        outputPortByte(masterPicDataAddress, ICW4_8086);
        ioWait();
        outputPortByte(slavePicDataAddress, ICW4_8086);
        ioWait();

        //
        outputPortByte(masterPicDataAddress, 0);
        ioWait();
        outputPortByte(slavePicDataAddress, 0);
        ioWait();
    }

    void sendEoiFlag(uint32_t interruptCode) {
        if(interruptCode >= 8) {
            outputPortByte(slavePicAddress, picEoiFlag);
        }

        outputPortByte(masterPicAddress, picEoiFlag);
    }
}

