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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_STATE_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_STATE_H

#include "iterator.h"
#include "formatter/formatter.h"

namespace std {

    // Forward declaration of the format argument
    template<class State>
    class BasicFormatArgument;

    // Forward declaration of the format arguments
    template<class State>
    class BasicFormatArguments;

    /**
     * The format state contains all of the state relating to the arguments values and
     * output of the formatted values.
     *
     * This class will keep the @tparam OutputIterator that points to the next position
     * to output a formatted value.
     *
     * It also contains the indexed arguments that are used by the format methods to
     * get the required argument for the Formatter.
     */
    template<class Type, class OutputIterator>
    class BasicFormatState {
        BasicFormatArguments<BasicFormatState> arguments_;
        OutputIterator& outputIterator_;

    public:
        using Iterator = OutputIterator;

        template<class T>
        using FormatterType = std::Formatter<T, Type>;
        using CharacterType = Type;

        // Constructors
        explicit BasicFormatState(
            BasicFormatArguments<BasicFormatState>& arguments,
            OutputIterator& outputIterator
        ) : arguments_(arguments), outputIterator_(outputIterator) { }

        // Accessors
        auto argument(std::size_t index) const -> BasicFormatArgument<BasicFormatState> {
            return arguments_.get(index);
        }

        auto out() -> Iterator {
            return outputIterator_;
        }

        void advanceTo(Iterator iterator) {
            outputIterator_ = iterator;
        }
    };

    // Declaration of a char based format state.
    using FormatState = BasicFormatState<char, char*>;
}


#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_STATE_H
