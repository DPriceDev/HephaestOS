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

#ifndef HEPHAIST_OS_DRIVERS_IO_IO_H
#define HEPHAIST_OS_DRIVERS_IO_IO_H

#include <stdoffset.h>

namespace kernel {

    extern "C" auto readFromPort(uint32_t port) -> uint8_t;

    extern "C" void writeToPort(uint32_t port, uint8_t value);

    inline void waitForIO() {
        constexpr static uint32_t TEST_POST_CODES_PORT = 0x80;
        writeToPort(TEST_POST_CODES_PORT, 0);
    }
}

#endif
////////////////////////////////////////////////////////////////////////////////