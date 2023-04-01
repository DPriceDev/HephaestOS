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

#ifndef HEPHAISTOS_THREADIDPROVIDER_H
#define HEPHAISTOS_THREADIDPROVIDER_H

#include <cstddef>
#include <cstdint>

namespace kernel {

    class ThreadIDProvider {
        std::size_t current = 0;

      public:
        auto getId() -> std::size_t;

        void returnId(std::size_t tid);
    };
}// namespace kernel

#endif// HEPHAISTOS_THREADIDPROVIDER_H
