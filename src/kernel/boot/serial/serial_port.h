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

#ifndef HEPHAISTOS_SERIAL_PORT_H
#define HEPHAISTOS_SERIAL_PORT_H

namespace kernel::boot {

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

    class SerialPortConnection;

    class SerialIterator {
        SerialPortConnection* connection;
        void (*write)(SerialPortConnection*, char);

    public:
        using iteratorType = SerialIterator;
        using valueType = char;
        using differenceType = int;
        using pointer = SerialIterator;
        using reference = SerialIterator&;

        SerialIterator(
            SerialPortConnection* connection,
            void (*write)(SerialPortConnection*, char)
        ) : connection(connection), write(write) { }

        SerialIterator& operator=(char character) {
            write(connection, character);
            return *this;
        }

        SerialIterator& operator*() {
            return *this;
        }

        constexpr SerialIterator& operator++() {
            return *this;
        }

        SerialIterator& operator++(int) {
            return *this;
        }
    };

    class SerialPortConnection {
        unsigned int portAddress;
        SerialIterator serialIterator {
            this,
            [] (SerialPortConnection* connection, char character) {
                connection->write(character);
            }
        };

    public:
        explicit SerialPortConnection(SerialPort port);

        ~SerialPortConnection() = default;

        // copy constructors
        SerialPortConnection(const SerialPortConnection&) = delete;

        SerialPortConnection& operator=(const SerialPortConnection&) = default;

        // move constructors
        SerialPortConnection(SerialPortConnection&&) noexcept = delete;

        SerialPortConnection& operator=(SerialPortConnection&&) noexcept = default;

        [[nodiscard]] bool open() const;

        void write(char character) const;

        auto out() -> SerialIterator*;
    };
}

#endif //HEPHAISTOS_SERIAL_PORT_H
