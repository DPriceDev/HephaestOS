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
#include <bit>

namespace kernel::boot {

    SerialPortConnection::SerialPortConnection(SerialPort port) : portAddress(
        static_cast<std::underlying_type<SerialPort>::type>(port)
    ) { }

    void SerialPortConnection::setModemControl(ModemControl&& controlRegister) const {
        auto registerByte = std::bit_cast<uint8_t>(controlRegister);
        outputPortByte(portAddress + MODEM_CONTROL_OFFSET, registerByte);
    }

    void SerialPortConnection::setEnabledInterrupts(const EnabledInterrupts&& interruptRegister) const {
        auto registerByte = std::bit_cast<uint8_t>(interruptRegister);
        outputPortByte(portAddress + INTERRUPT_REGISTER_OFFSET, registerByte);
    }

    void SerialPortConnection::writeToDataRegister(char character) const {
        outputPortByte(portAddress, character);
    }

    auto SerialPortConnection::readFromDataRegister() const -> uint8_t {
        return inputPortByte(portAddress);
    }

    auto SerialPortConnection::getLineStatus() const -> LineStatus {
        auto inputByte = inputPortByte(portAddress + LINE_STATUS_OFFSET);
        return std::bit_cast<LineStatus>(inputByte);
    }


    bool SerialPortConnection::open() {
        setEnabledInterrupts(EnabledInterrupts::None());

        outputPortByte(portAddress + 3, 0x80);    // Enable DLAB (set baud rate divisor)

        writeToDataRegister(0x3); // Set divisor to 3 (lo byte) 38400 baud
        setEnabledInterrupts(EnabledInterrupts::None());

        outputPortByte(portAddress + 3, 0x03);    // 8 bits, no parity, one stop bit
        outputPortByte(portAddress + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold

        setModemControl({
            .dataTerminalReady = true,
            .requestToSend = true,
            .interruptsEnabled = true,
            .isLoopback = true
        });

        // Test serial chip (send byte 0xAE and check if serial returns same byte)
        writeToDataRegister(0xAE);

        // Check if serial is faulty (i.e: not same byte as sent)
        if (readFromDataRegister() != 0xAE) {
            return false;
        }

        // If serial is not faulty set it in normal operation mode
        // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
        setModemControl({
            .dataTerminalReady = true,
            .requestToSend = true,
            .outputOne = true,
            .interruptsEnabled = true
        });

        return true;
    }

    void SerialPortConnection::write(char character) const {
        while (getLineStatus().transmitterBufferEmpty == false) { };

        writeToDataRegister(character);
    }
}
