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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_VARIANT_VISITOR_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_VARIANT_VISITOR_H

#include <array.h>
#include <bits/move.h>
#include <type_traits>

#include "parameter_pack.h"
#include "variant_get.h"
#include "variant_variant.h"

namespace std {

    namespace detail {

        /**
         * This struct is templated to the specific @tparam Variant Types for a given
         * @tparam Visitor.
         *
         * This is the intermediate struct that will be called if the size is greater than 0.
         *
         * The whole array builder structs work by looping through each struct for a given
         * overall size count, and building the common function type. The current type is
         * always appended to the end of the Types array again so that they are available
         * to build the array in the last struct.
         */
        template<class Visitor, class Variant, std::size_t Size, class FunctionType, class Type, class... Types>
        struct VariantVisitorArrayBuilder
            : public VariantVisitorArrayBuilder<
                  Visitor,
                  Variant,
                  Size - 1,
                  std::common_type_t<FunctionType, decltype([](Visitor&& visitor, Variant& variant) {
                                         return visitor(std::get<Type>(variant));
                                     })>,
                  Types...,
                  Type> {};

        /**
         * This struct is templated to the specific @tparam Variant Types for a given
         * @tparam Visitor.
         *
         * This the last struct that is called when the size drops to zero.
         *
         * The whole array builder structs work by looping through each struct for a given
         * overall size count, and building the common function type.
         * This last struct takes the current type and converts it to a visitor function,
         * then takes the other Types and converts those to visitor functions, and
         * adds them all to a visitor function array with the type of FunctionType.
         */
        template<class Visitor, class Variant, class FunctionType, class Type, class... Types>
        struct VariantVisitorArrayBuilder<Visitor, Variant, 0, FunctionType, Type, Types...> {

            static constexpr auto function = [](Visitor&& visitor, Variant& variant) {
                return visitor(std::get<Type>(variant));
            };

            static constexpr auto array =
                std::Array<std::common_type_t<FunctionType, decltype(function)>, sizeof...(Types) + 1> {
                    function,
                    [](Visitor&& visitor, Variant& variant) { return visitor(std::get<Types>(variant)); }...
                };
        };

        /**
         * This struct is templated to the specific @tparam Variant Types for a given
         * @tparam Visitor.
         *
         * This initial struct sets up the first function type that will be used to
         * build the common array type.
         *
         * The whole array builder structs work by looping through each struct for a given
         * overall size count, and building the common function type. The current type is
         * always appended to the end of the Types array again so that they are available
         * to build the array in the last struct.
         */
        template<class Visitor, class Variant, std::size_t Size, class Type, class... Types>
        struct VariantVisitorArray
            : public VariantVisitorArrayBuilder<
                  Visitor,
                  Variant,
                  Size - 1,
                  decltype([](Visitor&& visitor, Variant& variant) { return visitor(std::get<Type>(variant)); }),
                  Types...,
                  Type> {};

        /**
         * This retrieves the visitor array from a compile time struct that constructs
         * the array.
         */
        template<class Visitor, class Variant, class... Types>
        constexpr auto getVisitorArray(std::Variant<Types...>&) -> decltype(auto) {
            return VariantVisitorArray<Visitor, Variant, sizeof...(Types), Types...>::array;
        }
    }// namespace detail

    /**
     * Visit takes a given variant.h and applies it to a visitor
     * function. The visitor function will call the corresponding method
     * associated to the active indexes and types in each variant.h.
     */
    template<class Visitor, class Variant>
    constexpr auto visit(Visitor&& visitor, Variant& variant) -> decltype(auto) {
        auto array = detail::getVisitorArray<Visitor, Variant>(variant);
        return array[variant.index()](std::forward<Visitor>(visitor), variant);
    }

    /**
     * Visit takes a given variant.h and applies it to a visitor
     * function. The visitor function will call the corresponding method
     * associated to the active indexes and types in each variant.h.
     */
    template<class Visitor, class Variant>
    constexpr auto visit(Visitor& visitor, Variant& variant) -> decltype(auto) {
        return std::visit(std::move(visitor), variant);
    }

    // todo: Comment
    template<typename... Functions>
    struct Visitors : Functions... {
        using Functions::operator()...;
    };

    template<typename... Functions>
    Visitors(Functions...) -> Visitors<Functions...>;
}// namespace std

#endif// HEPHAIST_OS_SHARED_LIBRARY_CPP_VARIANT_VISITOR_H
