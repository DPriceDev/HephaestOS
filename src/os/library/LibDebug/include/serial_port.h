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

#ifndef HEPHAISTOS_SERIAL_PORT_H
#define HEPHAISTOS_SERIAL_PORT_H

#include <cstdint>

namespace debug {
    constexpr uint32_t DATA_REGISTER_OFFSET = 0;
    constexpr uint32_t DLAB_HIGH_BYTE_OFFSET = 1;
    constexpr uint32_t DLAB_LOW_BYTE_OFFSET = 0;
    constexpr uint32_t INTERRUPT_REGISTER_OFFSET = 1;
    constexpr uint32_t FIFO_CONTROL_OFFSET = 2;
    constexpr uint32_t LINE_CONTROL_OFFSET = 3;
    constexpr uint32_t MODEM_CONTROL_OFFSET = 4;
    constexpr uint32_t LINE_STATUS_OFFSET = 5;
    constexpr uint32_t MODEM_STATUS_OFFSET = 6;

    enum class SerialPort : unsigned int {
        COM1 = 0x3F8,
        COM2 = 0x2F8,
        COM3 = 0x3E8,
        COM4 = 0x2E8,
        COM5 = 0x5F8,
        COM6 = 0x4F8,
        COM7 = 0x5E8,
        COM8 = 0x4E8
    };

    struct DivisorLatchSettings {
        uint8_t low;
        uint8_t high;
    };

    struct [[gnu::packed]] ModemControl {
        bool dataTerminalReady : 1 = false;
        bool requestToSend : 1 = false;
        bool outputOne : 1 = false;
        bool interruptsEnabled : 1 = false;
        bool isLoopback : 1 = false;
        uint8_t /* Unused padding */ : 3;
    };

    struct [[gnu::packed]] EnabledInterrupts {
        bool dataAvailable : 1 = false;
        bool transmitterEmpty : 1 = false;
        bool breakOrError : 1 = false;
        bool statusChanged : 1 = false;
        uint8_t /* Unused padding */ : 4;

        static EnabledInterrupts None() {
            return { };
        }
    };

    struct [[gnu::packed]] LineStatus {
        bool dataReady : 1 = false;
        bool overrunError : 1 = false;
        bool parityError : 1 = false;
        bool framingError : 1 = false;
        bool breakIndicator : 1 = false;
        bool transmitterBufferEmpty : 1 = false;
        bool transmitterEmpty : 1 = false;
        bool impendingError : 1 = false;
    };

    enum class StopBit {
        ONE = 0,
        TWO = 1
    };

    enum class DataLength : uint8_t {
        FIVE_BITS = 0,
        SIX_BITS = 1,
        SEVEN_BITS = 2,
        EIGHT_BITS = 3
    };

    enum Parity {
        NONE = 0,
        ODD = 1,
        EVEN = 2,
        MARK = 3,
        SPACE = 4
    };

    struct [[gnu::packed]] LineControl {
        DataLength dataLength: 2 = DataLength::FIVE_BITS;
        StopBit stopBit : 1 = StopBit::ONE;
        Parity parity : 3 = Parity::NONE;
        bool isBreakEnable: 1 = false;
        // DLAB
        bool divisorLatchAccess : 1 = false;
    };

    enum class FIFOInterruptThreshold : uint8_t {
        BYTE_1,
        BYTE_4,
        BYTE_8,
        BYTE_14
    };

    struct [[gnu::packed]] FIFOControl {
        bool isEnabled: 1 = false;
        bool clearReceive: 1 = false;
        bool clearTransmit: 1 = false;
        bool isDMAMode: 1 = false;
        bool /* unused */ : 1;
        bool is64Bit : 1 = false;
        FIFOInterruptThreshold interruptThreshold: 2;
    };

    class SerialPortConnection {
        unsigned int portAddress;

        void setModemControl(ModemControl&& controlRegister) const;

        void setEnabledInterrupts(const EnabledInterrupts&& interruptRegister) const;

        void setLineControl(const LineControl&& lineControl) const;

        void setFIFOControl(const FIFOControl&& fifoControl) const;

        void writeToDataRegister(uint8_t character) const;

        [[nodiscard]] uint8_t readFromDataRegister() const;

        void setBaudRate(uint32_t baudRate) const;

    public:
        constexpr static uint32_t DEFAULT_BAUD_RATE = 38400;

        explicit SerialPortConnection(SerialPort port);

        ~SerialPortConnection() = default;

        // copy constructors
        SerialPortConnection(const SerialPortConnection&) = delete;

        SerialPortConnection& operator=(const SerialPortConnection&) = default;

        // move constructors
        SerialPortConnection(SerialPortConnection&&) noexcept = delete;

        SerialPortConnection& operator=(SerialPortConnection&&) noexcept = default;

        [[nodiscard]] bool open(uint32_t baudRate = DEFAULT_BAUD_RATE) const;

        void write(char character) const;

        [[nodiscard]] LineStatus getLineStatus() const;
    };
}

#endif //HEPHAISTOS_SERIAL_PORT_H
