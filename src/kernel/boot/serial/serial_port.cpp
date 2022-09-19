// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaistOS.
//
// HephaistOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaistOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
//

#include "serial_port.h"
#include <type_traits>
#include "boot/io.h"

namespace kernel::boot {

//    bool SerialPortConnection::open() const {
//        outputPortByte(portAddress + 1, 0x00);    // Disable all interrupts
//        outputPortByte(portAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)
//        outputPortByte(portAddress + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
//        outputPortByte(portAddress + 1, 0x00);    //                  (hi byte)
//        outputPortByte(portAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
//        outputPortByte(portAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
//        outputPortByte(portAddress + 4, 0x0B);    // IRQs enabled, RTS/DSR set
//        outputPortByte(portAddress + 4, 0x1E);    // Set in loopback mode, test the serial chip
//
//        // Test serial chip (send byte 0xAE and check if serial returns same byte)
//        outputPortByte(portAddress + 0, 0xAE);
//
//        // Check if serial is faulty (i.e: not same byte as sent)
//        if (inputPortByte(portAddress + 0) != 0xAE) {
//            return false;
//        }
//
//        // If serial is not faulty set it in normal operation mode
//        // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
//        outputPortByte(portAddress + 4, 0x0F);
//        return true;
//    }

//    int isNotTransmitting(unsigned int portAddress) {
//        return inputPortByte(portAddress + 5) & 0x20;
//    }
//
//    void SerialPortConnection::write(char character) const {
//        while (isNotTransmitting(portAddress) == 0);
//
//        outputPortByte(portAddress, character);
//    }
//
//    auto SerialPortConnection::out() -> SerialIterator* {
//        return &serialIterator;
//    }
}
