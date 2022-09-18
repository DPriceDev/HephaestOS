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

    /**
     * std::MonoState,
     * bool,
     * characterType,
     * int,
     * unsigned int,
     * long long int,
     * unsigned long long int,
     * float,
     * double,
     * long double,
     * const characterType*,
     * BaseStringView<characterType>,
     * const void*,
     * handle
     * @tparam State
     */

    // todo
    template<class State>
    class BasicFormatArgument {
    public:
        class handle;

        using characterType = typename State::characterType;

        BasicFormatArgument() : value(
                std::Variant<
                        std::MonoState,
                        bool,
                        characterType,
                        int,
                        unsigned int,
//                        long int,
                        unsigned long,
                        unsigned long long int,
                        //float,
                        //double,
                        //long double,
                        const characterType*,
                        BaseStringView<characterType>,
                        const void*
                        //handle
            >(std::MonoState())
        ) { }

        template<class Type>
        explicit BasicFormatArgument(Type&& type) : value(
                std::Variant<
                        std::MonoState,
                        bool,
                        characterType,
                        int,
                        unsigned int,
//                        long int,
                        unsigned long,
                        unsigned long long int,
                        //float,
                        //double,
                        //long double,
                        const characterType*,
                        BaseStringView<characterType>,
                        const void*
                        //handle
                >(std::forward<Type>(type))
        ) { }

//    private:

        std::Variant<
            std::MonoState,
            bool,
            characterType,
            int,
            unsigned int,
//            long int,
            unsigned long,
            unsigned long long int,
//            float,
//            double,
//            long double,
            const characterType*,
            BaseStringView<characterType>,
            const void*
//            handle
        > value;

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
