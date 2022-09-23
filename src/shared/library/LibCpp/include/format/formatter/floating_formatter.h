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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FLOATING_FORMATTER_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FLOATING_FORMATTER_H

#include <limits>
#include <cfloat>

#include "formatter.h"

namespace std {

    /**
     * This specialises the Formatter for any Type that is floating point.
     * i.e. float, double, long double.
     *
     * This outputs the floating point number using std::toChars. This will
     * output the entire number regardless of length.
     * The behaviour is undefined if the output container is too small.
     */
    template<std::floating_point Type>
    struct Formatter<Type> {

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(std::floating_point auto& floating, auto& state) {
            auto output = state.out();
            auto buffer = std::Array<char, DBL_MAX_10_EXP> { };
            auto result = std::toChars(buffer.begin(), buffer.end(), floating);

            std::forEach(buffer.begin(), result, [&output] (char character) {
                *output++ = character;
            });

            return output;
        }
    };
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FLOATING_FORMATTER_H
