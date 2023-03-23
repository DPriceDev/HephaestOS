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

#include "parse_state.h"
#include "string_view.h"
#include "variant_base.h"

namespace std {

    /**
     * This concept defines what is a valid satandard argument.
     * A standard argument is any of the arguments accepted by
     * BasicFormatArgument, except customt types that will be stored as
     * BasicFormatArgument::Handle.
     */
    template<class Type, class CharacterType>
    concept StandardFormatArgument =
        std::is_same_v<Type, bool&> || std::is_same_v<Type, CharacterType&> || std::is_same_v<Type, int&>
        || std::is_same_v<Type, unsigned int&> || std::is_same_v<Type, long int&>
        || std::is_same_v<Type, unsigned long&> || std::is_same_v<Type, unsigned long long int&>
        || std::is_same_v<Type, float&> || std::is_same_v<Type, double&> || std::is_same_v<Type, long double&>
        || std::is_same_v<Type, const CharacterType*&> || std::is_same_v<Type, const void*&>
        || std::convertible_to<Type, const CharacterType*> || std::is_same_v<Type, BaseStringView<CharacterType>&>;

    /**
     * This concept defines a custom format argument which is basically anything
     * that is not a standard argument, but more specifically, it is any custom
     * argument that will be converted to a BasicFormatArgument::Handle.
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
        class Handle;

        using CharacterType = typename State::CharacterType;

        // Defines a variant.h type that accepts all standard format types, and the Handle type.
        using ArgumentVariant = std::Variant<
            std::MonoState,
            bool,
            CharacterType,
            int,
            unsigned int,
            long int,
            unsigned long,
            unsigned long long int,
            float,
            double,
            long double,
            const CharacterType*,
            BaseStringView<CharacterType>,
            const void*,
            Handle>;

        // Constructors
        BasicFormatArgument() : value_(ArgumentVariant(std::MonoState())) {}

        /**
         * Constructs any standard argument (not a Handle type) by directly
         * passing the @param type into the variant.h.
         */
        template<StandardFormatArgument<typename State::CharacterType> Type>
        explicit BasicFormatArgument(Type& type) : value_(ArgumentVariant(type)) {}

        /**
         * Constructs any custom type, by wrapping the @param type in the Handle
         * class and then passing it into the variant.h.
         */
        template<CustomFormatArgument<typename State::CharacterType> Type>
        explicit BasicFormatArgument(Type& type) : value_(ArgumentVariant(Handle(type))) {}

        // todo: make this private:

        // todo: friend make function

        // todo: friend getVisitorArray?

        ArgumentVariant value_;

        // todo: operator bool
    };

    /**
     * TODO: Comment
     * @tparam State
     */
    template<class State>
    class BasicFormatArgument<State>::Handle {
        using CharacterType = typename State::CharacterType;

        // Type erased pointer to the stored Type that will be recast and used in formatType.
        const void* data_ { nullptr };

        // Function pointer that will contain formatType for a given Type.
        // todo: replace with std function?
        void (*formatFunction_)(BasicParseState<CharacterType>&, State&, const void*) { nullptr };

        /**
         * Static method that can be specialized for a given @tparam Type; the @tparam Type will be
         * used to construct the specialized Formatter for custom Type. The type erased @param pointer
         * will be cast to the @tparam Type and parsed and formatted by the formatter.
         */
        template<class Type>
        static void formatType(BasicParseState<CharacterType>& parseState, State& formatState, const void* pointer) {
            typename State::template FormatterType<Type> formatter;
            parseState.advanceTo(formatter.parse(parseState));
            const auto newType = *static_cast<const Type*>(pointer);
            formatState.advanceTo(formatter.format(newType, formatState));
        }

      public:
        // Constructors
        Handle() = default;

        /**
         * Constructs the Handle from a @param type; by erasing the type and storing it in data.
         * Passes a pointer to the static method formatType specialized for the @tparam Type to formatFunction.
         */
        template<class Type>
        explicit Handle(const Type& type) : data_(std::addressof(type)), formatFunction_(this->formatType<Type>) {}

        /**
         * This can be called to format the stored data, to the output stored in the @param formatState.
         * This calls the underlying formatFunction with the provided states, and the erased data.
         */
        void format(BasicParseState<CharacterType>& parseState, State& formatState) const {
            formatFunction_(parseState, formatState, data_);
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
            argument.value_
        );
    }
}// namespace std

#endif// HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMAT_ARGUMENT_H
