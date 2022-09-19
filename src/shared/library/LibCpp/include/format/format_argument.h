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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENT_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENT_H

#include "variant_base.h"
#include "string_view.h"
#include "parse_state.h"

namespace std {

    /**
     * This concept defines what is a valid satandard argument.
     * A standard argument is any of the arguments accepted by
     * BasicFormatArgument, except customt types that will be stored as
     * BasicFormatArgument::handle.
     */
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

    /**
     * This concept defines a custom format argument which is basically anything
     * that is not a standard argument, but more specifically, it is any custom
     * argument that will be converted to a BasicFormatArgument::handle.
     */
    template<class CharacterType, class Type>
    concept CustomFormatArgument = !StandardFormatArgument<CharacterType, Type>;

    /**
     * TODO: Comment
     * @tparam State
     */
    template<class State>
    class BasicFormatArgument {
    public:
        class handle;

        using characterType = typename State::characterType;

        // Defines a variant.h type that accepts all standard format types, and the handle type.
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

        // Constructors
        BasicFormatArgument() : value(
            ArgumentVariant(std::MonoState())
        ) { }

        /**
         * Constructs any standard argument (not a handle type) by directly
         * passing the @param type into the variant.h.
         */
        template<StandardFormatArgument<typename State::characterType> Type>
        explicit BasicFormatArgument(Type&& type) : value(
            ArgumentVariant(std::forward<Type>(type))
        ) { }

        /**
         * Constructs any custom type, by wrapping the @param type in the handle
         * class and then passing it into the variant.h.
         */
        template<CustomFormatArgument<typename State::characterType> Type>
        explicit BasicFormatArgument(Type&& type) : value(
            ArgumentVariant(handle(std::forward<Type>(type)))
        ) { }

        // todo: make this private:

        // todo: friend make function

        // todo: friend getVisitorArray?

        ArgumentVariant value;

        // todo: operator bool
    };

    /**
     * TODO: Comment
     * @tparam State
     */
    template<class State>
    class BasicFormatArgument<State>::handle {
        using characterType = typename State::characterType;

        // Type erased pointer to the stored Type that will be recast and used in formatType.
        const void* data { nullptr };

        // Function pointer that will contain formatType for a given Type.
        void (* formatFunction)(BasicParseState<characterType>&, State&, const void*) { nullptr };

        /**
         * Static method that can be specialized for a given @tparam Type; the @tparam Type will be
         * used to construct the specialized Formatter for custom Type. The type erased @param pointer
         * will be cast to the @tparam Type and parsed and formatted by the formatter.
         */
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
        // Constructors
        handle() = default;

        /**
         * Constructs the handle from a @param type; by erasing the type and storing it in data.
         * Passes a pointer to the static method formatType specialized for the @tparam Type to formatFunction.
         */
        template<class Type>
        explicit handle(Type type) : data(std::addressof(type)), formatFunction(this->formatType < Type > ) { }

        /**
         * This can be called to format the stored data, to the output stored in the @param formatState.
         * This calls the underlying formatFunction with the provided states, and the erased data.
         */
        void format(BasicParseState<characterType>& parseState, State& formatState) const {
            formatFunction(parseState, formatState, data);
        }
    };

    /**
     * Visitor method wraps std::visit which is used to getVisitorArray the basic argument.
     * The result is converted to the raw argument, or to a MonoState if the argument
     * is invalid.
     */
    template<class Visitor, class State>
    auto visitFormatArgument(Visitor&& visitor, std::BasicFormatArgument<State> argument) {
        return std::visit(
            [&visitor](auto result) -> decltype(auto) {
                if (!result.isValid()) {
                    return visitor(std::MonoState());
                }

                return visitor(result.get());
            },
            argument.value
        );
    }
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENT_H
