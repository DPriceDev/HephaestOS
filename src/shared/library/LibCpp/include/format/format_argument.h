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

#ifndef HEPHAISTOS_FORMAT_ARGUMENT_H
#define HEPHAISTOS_FORMAT_ARGUMENT_H

#include "variant.h"
#include "string_view.h"

namespace std {

    // todo
    template<class State>
    class BasicFormatArgument {
    public:
        class handle;

        BasicFormatArgument() : value(
                std::Variant<
                        std::MonoState,
                        char
            >(std::MonoState())
        ) { }

        template<class Type>
        explicit BasicFormatArgument(Type&& type) : value(
                std::Variant<
                        std::MonoState,
                        char
                >(std::forward<Type>(type))
        ) { }

//    private:
        using characterType = typename State::characterType;

        // todo: need to add all types
        std::Variant<std::MonoState, char> value;

        // todo: operator bool
    };

    // todo
    template<class State>
    class BasicFormatArgument<State>::handle {

    };

    /**
     *
     * @tparam Visitor
     * @tparam State
     * @param visitor
     * @param argument
     * @return
     */
    template<class Visitor, class State>
    auto visitFormatArgument(Visitor&& visitor, std::BasicFormatArgument<State> argument) {
        return std::visit(
                [&visitor] (auto result) -> decltype(auto) {
                    if (!result.isValid()) {
                        return visitor(std::MonoState());
                    }

                    return visitor(result.get());
                },
                argument.value
        );
    }
}

#endif //HEPHAISTOS_FORMAT_ARGUMENT_H
