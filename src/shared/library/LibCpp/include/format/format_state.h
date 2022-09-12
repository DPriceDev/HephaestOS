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
#include "formatter/formatter.h"

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
        BasicFormatArguments<BasicFormatState> arguments;
        OutputIterator outputIterator;

    public:
        using iterator = OutputIterator;
        using characterType = CharacterType;

        template<class T>
        using formatterType = std::Formatter<T, CharacterType>;

        explicit BasicFormatState(
                BasicFormatArguments<BasicFormatState>& arguments,
                OutputIterator& outputIterator
        ) : arguments(arguments), outputIterator(outputIterator) { }

        auto argument(std::size_t index) const -> BasicFormatArgument<BasicFormatState> {
            return arguments.get(index);
        }

        auto out() -> iterator {
            return outputIterator;
        }

        void advanceTo(iterator iterator) {
            outputIterator = iterator;
        }
    };

    // todo
    // todo back insert?
    using FormatState = BasicFormatState<char, char*>;
}


#endif //HEPHAISTOS_FORMAT_STATE_H
