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

#ifndef HEPHAISTOS_THREADCONTROLBLOCK_H
#define HEPHAISTOS_THREADCONTROLBLOCK_H

#include <stdint.h>

namespace kernel {

    using TID = std::size_t;

    // todo: Abstract
    struct ThreadRegisters {
        uint32_t eax = 0;
    };

    struct ThreadControlBlock {
        TID id = 0;
        uintptr_t stack = 0;
        uintptr_t instruction = 0;
        ThreadRegisters registers = ThreadRegisters { };
    };
}

#endif// HEPHAISTOS_THREADCONTROLBLOCK_H
