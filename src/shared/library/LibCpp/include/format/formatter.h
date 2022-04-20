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

#ifndef HEPHAISTOS_FORMATTER_H
#define HEPHAISTOS_FORMATTER_H

namespace std {

    // todo
    template<class Type, class CharacterType = char>
    struct Formatter;

    /**
     * Char specification
     * todo
     */
    template<>
    struct Formatter<char> {

        // todo: step over iterator until } is hit and save parameters to formatter
        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };
            if(iterator == end || *iterator == '}') {

            }

            return ++iterator;
        }

        // print character, increment iterator and return
        // todo: Pick up formatter rules and print out character with specific rules
        auto format(const char& character, auto& state) {
            &state.out() = character;
            state.out() = state.out()++;
            return state.out();
        }
    };

}


#endif //HEPHAISTOS_FORMATTER_H
