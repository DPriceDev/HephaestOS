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

export module os.kernel.thread.id;

namespace kernel {
    export class ThreadIDProvider {
        std::size_t current = 0;

    public:
        auto getId() -> std::size_t;

        void returnId(std::size_t tid);
    };
}

auto kernel::ThreadIDProvider::getId() -> std::size_t {
    std::size_t const tid = current;
    current++;
    return tid;
}

void kernel::ThreadIDProvider::returnId(std::size_t) {
    // todo: Return id for reuse
}
