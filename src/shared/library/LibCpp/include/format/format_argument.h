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
#include "parse_state.h"

namespace std {

    template<class Type, class CharacterType>
    concept StandardFormatArgument = std::is_same_v<Type, bool&> ||
        std::is_same_v<Type, CharacterType&> ||
        std::is_same_v<Type, int&> ||
        std::is_same_v<Type, unsigned int&> ||
        std::is_same_v<Type, long int&> ||
        std::is_same_v<Type, unsigned long&> ||
        std::is_same_v<Type, unsigned long long int&> ||
        std::is_same_v<Type, float&> ||
        std::is_same_v<Type, double&> ||
        std::is_same_v<Type, long double&> ||
        std::is_same_v<Type, const CharacterType*&> ||
        std::is_same_v<Type, const void*&> ||
        std::convertible_to<Type, const CharacterType*> ||
        std::is_same_v<Type, BaseStringView<CharacterType>&>;

    template<class CharacterType, class Type>
    concept CustomFormatArgument = !StandardFormatArgument<CharacterType, Type>;

    // todo
    template<class State>
    class BasicFormatArgument {
    public:
        class handle;
        using characterType = typename State::characterType;

        using ArgumentVariant = std::Variant<
            std::MonoState,
            bool,
            characterType,
            int,
            unsigned int,
            long int,
            unsigned long,
            unsigned long long int,
            float,
            double,
            long double,
            const characterType*,
            BaseStringView<characterType>,
            const void*,
            handle
        >;

        BasicFormatArgument () : value(
            ArgumentVariant(std::MonoState())
        ) { }

        template<StandardFormatArgument<typename State::characterType> Type>
        explicit BasicFormatArgument (Type&& type) : value(
            ArgumentVariant(std::forward<Type>(type))
        ) { }

        template<CustomFormatArgument<typename State::characterType> Type>
        explicit BasicFormatArgument (Type&& type) : value(
            ArgumentVariant(handle(std::forward<Type>(type)))
        ) { }

        // todo: make this    private:

        // todo: friend make function

        // todo: friend visit?

        ArgumentVariant value;

        // todo: operator bool
    };

    // todo
    template<class State>
    class BasicFormatArgument<State>::handle {
        using characterType = typename State::characterType;

        const void * data{ nullptr };
        void (*formatFunction)(BasicParseState<characterType>&, State&, const void*) { nullptr };

        template<class Type>
        static void formatType(
            BasicParseState<characterType>& parseState,
            State& formatState,
            const void* pointer
        ) {
            typename State::template formatterType<Type> formatter;
            parseState.advanceTo(formatter.parse(parseState));
            auto newType = *static_cast<const Type*>(pointer);
            formatState.advanceTo(formatter.format(newType, formatState));
        }

    public:
        handle() = default;

        template<class Type>
        explicit handle(Type type) : data(std::addressof(type)), formatFunction(this->formatType<Type>) { }

        void format(
            BasicParseState<typename State::characterType> &parseState,
            State &formatState
        ) const {
            formatFunction(parseState, formatState, data);
        }
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
    auto visitFormatArgument (Visitor&& visitor, std::BasicFormatArgument<State> argument) {
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
