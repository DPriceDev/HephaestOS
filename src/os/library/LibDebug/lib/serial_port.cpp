// Copyright (C) 2023 David Price - All Rights Reserved
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
#include "io.h"
#include <bit>
#include <type_traits>

namespace debug {

    /**
     * TODO: Comment
     * @param port
     */
    SerialPortConnection::SerialPortConnection(SerialPort port)
        : portAddress(static_cast<std::underlying_type<SerialPort>::type>(port)) {}

    /**
     * TODO: Comment
     * @param controlRegister
     */
    void SerialPortConnection::setModemControl(ModemControl&& controlRegister) const {
        auto registerByte = std::bit_cast<uint8_t>(controlRegister);
        hal::writeToPort(portAddress + MODEM_CONTROL_OFFSET, registerByte);
    }

    /**
     * TODO: Comment
     * @param interruptRegister
     */
    void SerialPortConnection::setEnabledInterrupts(const EnabledInterrupts&& interruptRegister) const {
        auto registerByte = std::bit_cast<uint8_t>(interruptRegister);
        hal::writeToPort(portAddress + INTERRUPT_REGISTER_OFFSET, registerByte);
    }

    /**
     * TODO: Comment
     * @param lineControl
     */
    void SerialPortConnection::setLineControl(const LineControl&& lineControl) const {
        auto registerByte = std::bit_cast<uint8_t>(lineControl);
        hal::writeToPort(portAddress + LINE_CONTROL_OFFSET, registerByte);
    }

    /**
     * TODO: Comment
     * @param fifoControl
     */
    void SerialPortConnection::setFIFOControl(const FIFOControl&& fifoControl) const {
        auto registerByte = std::bit_cast<uint8_t>(fifoControl);
        hal::writeToPort(portAddress + FIFO_CONTROL_OFFSET, registerByte);
    }

    /**
     * TODO: Comment
     * @param character
     */
    void SerialPortConnection::writeToDataRegister(uint8_t character) const {
        hal::writeToPort(portAddress + DATA_REGISTER_OFFSET, character);
    }

    /**
     * TODO: Comment
     * @return
     */
    auto SerialPortConnection::readFromDataRegister() const -> uint8_t {
        return hal::readFromPort(portAddress + DATA_REGISTER_OFFSET);
    }

    /**
     * TODO: Comment
     * @return
     */
    auto SerialPortConnection::getLineStatus() const -> LineStatus {
        auto inputByte = hal::readFromPort(portAddress + LINE_STATUS_OFFSET);
        return std::bit_cast<LineStatus>(inputByte);
    }

    /**
     * TODO: Comment
     * @param baudRate
     */
    auto SerialPortConnection::setBaudRate(uint32_t baudRate) const -> void {
        setLineControl(LineControl { .divisorLatchAccess = true });

        constexpr static uint32_t MAX_BAUD_RATE = 115200;
        const auto divisor = static_cast<uint16_t>(MAX_BAUD_RATE / baudRate);
        const auto settings = std::bit_cast<DivisorLatchSettings>(divisor);

        hal::writeToPort(portAddress + DLAB_LOW_BYTE_OFFSET, settings.low);
        hal::writeToPort(portAddress + DLAB_HIGH_BYTE_OFFSET, settings.high);

        setLineControl(LineControl { .divisorLatchAccess = false });
    }

    /**
     * TODO: Comment
     * @param baudRate
     * @return
     */
    bool SerialPortConnection::open(uint32_t baudRate) const {
        setEnabledInterrupts(EnabledInterrupts::None());

        setBaudRate(baudRate);

        setLineControl(LineControl {
            .dataLength = DataLength::EIGHT_BITS, .stopBit = StopBit::ONE, .parity = Parity::NONE });

        setFIFOControl(FIFOControl { .isEnabled = true,
                                     .clearReceive = true,
                                     .clearTransmit = true,
                                     .interruptThreshold = FIFOInterruptThreshold::BYTE_14 });

        setModemControl(
            { .dataTerminalReady = true, .requestToSend = true, .interruptsEnabled = true, .isLoopback = true }
        );

        // Test serial chip
        constexpr static uint8_t testChar = 0xAE;
        writeToDataRegister(testChar);
        if (readFromDataRegister() != testChar) {
            return false;
        }

        // If serial is not faulty set it in normal operation mode
        setModemControl(
            { .dataTerminalReady = true, .requestToSend = true, .outputOne = true, .interruptsEnabled = true }
        );

        return true;
    }

    /**
     * TODO: Comment
     * @param character
     */
    void SerialPortConnection::write(char character) const {
        while (getLineStatus().transmitterBufferEmpty == false) {};

        writeToDataRegister(static_cast<uint8_t>(character));
    }
}// namespace debug
