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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_POINTER_FORMATTER_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_POINTER_FORMATTER_H

#include "formatter.h"
#include "int_formatter.h"
#include <bit>
#include <charconv.h>

namespace std {

    /**
     * Specializes the Formatter for void pointers.
     * This will output the pointer address, prepended with '0x'
     * e.g. '0x1234567890'.
     */
    template<>
    struct Formatter<const void*> {

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(const void* pointer, auto& state) {
            auto output = state.out();
            *output++ = '0';
            *output++ = 'x';
            state.advanceTo(output);

            const auto address = std::bit_cast<std::uintptr_t>(pointer);
            return Formatter<std::uintptr_t>().format(address, state);
        }
    };
}// namespace std

#endif// HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_POINTER_FORMATTER_H
