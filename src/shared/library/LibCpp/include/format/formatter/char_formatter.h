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

#ifndef HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_CHAR_FORMATTER_H
#define HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_CHAR_FORMATTER_H

#include "formatter.h"

namespace std {

    /**
     * Specializes the Formatter for char types.
     * This will currently print the character out verbatim.
     */
    template<>
    struct Formatter<char> {

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(const char& character, auto& state) {
            auto output = state.out();
            *output++ = character;
            return output;
        }
    };

    /**
     * Specializes the Formatter for const char* strings.
     * This will output the string verbatim until it hits a null terminator, and
     * will not output the null terminator.
     * The behaviour is undefined if it is not null terminated.
     */
    template<>
    struct Formatter<const char*> {

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(const char* string, auto& state) {
            auto output = state.out();
            while (*string != '\0') { *output++ = *string++; }
            return output;
        }
    };

    /**
     * This specializes the Formatter for a String View.
     * This will output the underlying string, not including a null
     * terminator.
     */
    template<>
    struct Formatter<BaseStringView<char>> {

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(BaseStringView<char> view, auto& state) {
            auto output = state.out();
            for (char character : view) { *output++ = character; }
            return output;
        }
    };
}// namespace std

#endif// HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_CHAR_FORMATTER_H
