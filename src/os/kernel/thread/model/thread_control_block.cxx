// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

module;

#include <cstdint>
#include <cstddef>

export module os.kernel.thread.control;

namespace kernel {

    export using TID = std::size_t;

    // todo: Abstract
    export struct ThreadRegisters {
        uint32_t eax = 0;
    };

    export struct thread_control_block {
        TID id = 0;
        uintptr_t stack = 0;
        uintptr_t instruction = 0;
        ThreadRegisters registers = ThreadRegisters {};
    };
}// namespace kernel

