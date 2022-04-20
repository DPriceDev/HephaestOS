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

#ifndef HEPHAISTOS_FORMAT_STATE_H
#define HEPHAISTOS_FORMAT_STATE_H

#include "iterator.h"

namespace std {

    // Forward declare
    template<class State>
    class BasicFormatArgument;

    // Forward declare
    template<class State>
    class BasicFormatArguments;

    // todo
    template<class CharacterType, outputIterator<const CharacterType&> OutputIterator>
    class BasicFormatState {
        BasicFormatArguments<BasicFormatState> args;
        OutputIterator outputIterator;

    public:
        using iterator = OutputIterator;
        using characterType = CharacterType;

        template<class T>
        using formatterType = Formatter<T, CharacterType>;

        auto argument(std::size_t id) const -> BasicFormatArgument<BasicFormatState> {
            // todo
        }

        auto out() -> iterator {
            // todo
        }

        void advanceTo(iterator iterator) {
            // todo
        }
    };

    // todo
    template<class CharacterType>
    class BasicFormatParseState {

    };

    // todo
    // todo back insert?
    using FormatState = BasicFormatState<char, char*>;
}


#endif //HEPHAISTOS_FORMAT_STATE_H
