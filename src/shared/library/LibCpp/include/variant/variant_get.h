// Copyright (C) 2022 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAEST_OS_SHARED_LIBRARY_CPP_VARIANT_VARIANT_GET_H
#define HEPHAEST_OS_SHARED_LIBRARY_CPP_VARIANT_VARIANT_GET_H

#include "optional.h"
#include "variant_variant.h"

namespace std {

    /**
     * @return the value where the type is the type at the @tparam TypeIndex
     * in the @tparam Types parameter pack. If the @tparam TypeIndex is not the
     * current active Variant Type, an exception is thrown.
     * @tparam Types are the Variants stored in @param variant.
     */
    template<std::size_t TypeIndex, class... Types>
    constexpr auto getIf(std::Variant<Types...>& variant) -> auto* {
        if (variant.index() != TypeIndex) {
            return nullptr;
        }

        using Type = typename VariantType<TypeIndex, Types...>::type;
        return static_cast<Type*>(variant.data());
    }

    /**
     * @return the value of type @tparam Type from the @tparam Types parameter
     * pack. If the @tparam Type is not the current active Variant Type,
     * an exception is thrown.
     * @tparam Types are the Variants stored in @param variant.
     */
    template<class Type, class... Types>
    constexpr auto getIf(std::Variant<Types...>& variant) -> Type* {
        auto getIndex = VariantIndex<0, Type, Types...>().index;
        if (getIndex != variant.index()) {
            return nullptr;
        }
        return static_cast<Type*>(variant.data());
    }

    /**
     * Returns the value stored in the @param variant at the given @tparam TypeIndex.
     * If the active index in the variant.h is not the same as the @tparam TypeIndex, then
     * a failure result is returned.
     */
    template<std::size_t TypeIndex, class... Types, class ResultType>
    constexpr auto get(std::Variant<Types...>& variant) -> std::Optional<ResultType> {
        if (variant.index() != TypeIndex) {
            return std::Optional<ResultType>();
        }

        using Type = typename VariantType<TypeIndex, Types...>::type;
        return std::Optional<ResultType>(*static_cast<Type*>(variant.data()));
    }

    /**
     * Returns the value stored in the @param variant if it is of the type @tparam Type.
     * If the active value in the variant.h is not of the type @tparam Type then a failure
     * result is returned.
     */
    template<class Type, class... Types>
    constexpr auto get(std::Variant<Types...>& variant) -> std::Optional<Type> {
        auto getIndex = VariantIndex<0, Type, Types...>().index;
        if (getIndex != variant.index()) {
            return std::Optional<Type>();
        }
        return std::Optional<Type>(*static_cast<Type*>(variant.data()));
    }
}// namespace std

#endif// HEPHAEST_OS_SHARED_LIBRARY_CPP_VARIANT_VARIANT_GET_H
