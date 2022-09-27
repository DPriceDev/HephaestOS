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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_VARIANT_VARIANT_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_VARIANT_VARIANT_H

#include <concepts>
#include <type_traits>

#include "parameter_pack.h"

namespace std {

    /**
     * MonoState can be a default state for a variant.h. This can be used to denote
     * an empty value if required.
     */
    struct MonoState { };

    /**
     * Variant Type takes an initial @tparam TypeIndex and walks @tparam NextTypes,
     * decrementing the @tparam TypeIndex until it is 0. When @tparam TypeIndex
     * is 0 it will call a specialized version of this struct.
     */
    template<size_t TypeIndex, class NextType, class... NextTypes>
    struct VariantType : VariantType<TypeIndex - 1, NextTypes...> { };

    /**
     * Specialized Variant Type for when the Type index has reached 0. When it
     * is zero, we know we have walked the Variant Types until we have reached
     * the Type at the index defined at the calling point.
     * @tparam IndexedType is set as the type alias to define the Type at the
     * chosen index.
     * @tparam UnusedTypes are the pack of Types after the chosen index.
     */
    template<class IndexedType, class... UnusedTypes>
    struct VariantType<0, IndexedType, UnusedTypes...> {
        using type = IndexedType;
    };

    /**
     * Variant Index walks the Types pack, incrementing @tparam Index as it goes,
     * until the @tparam TypeToMatch is equal to the @tparam NextType.
     * These are matched in a specialized version of this struct.
     */
    template<size_t Index, class TypeToMatch, class NextType, class... NextTypes>
    struct VariantIndex : VariantIndex<Index + 1, TypeToMatch, NextTypes...> { };

    /**
     * Specialized Variant Index where the @tparam MatchedType is both the
     * Type to match and the next type in the pack. When this is a case, we know
     * we have found the matched type and we can set the @param index as the
     * @tparam Index from walking the pack.
     */
    template<size_t Index, class MatchedType, class... UnusedTypes>
    struct VariantIndex<Index, MatchedType, MatchedType, UnusedTypes...> {
        size_t index = Index;
    };

    namespace detail {

        /**
         * Last method of linear destroy to cover no Types left to destroy.
         * todo: is it possible to build this as a const eval array of lambdas
         * todo: that take the data and index and calls the function pointer.
         */
        template<size_t>
        auto destroyLinear(size_t, void*) -> void { /* No destructor */ }

        /**
         * Takes the @tparam Type, Types and checks whether the @tparam Index
         * matches the current variant.h @param index and calls its
         * destructor if it matches.
         */
        template<size_t Index, class Type, class... Types>
        constexpr auto destroyLinear(size_t index, void* pointer) -> void {
            if (index == Index) {
                static_cast<Type*>(pointer)->~Type();
                return;
            }
            destroyLinear<Index + 1, Types...>(index, pointer);
        }

        /**
         * Storage for a variant.h of any number of types. This stores an un-typed
         * array of bytes/chars where the @tparam Size is the size in bytes of
         * the largest Type in the Variant Type pack.
         * This also stores the @param index of the currently active type
         * at its index in the Variant Type pack.
         */
        template<std::size_t Size>
        struct VariantStorage {
            char data[Size] { };
            size_t index { 0 };
        };
    }

    /**
     * Variant holds a Type which is part of the pack of @tparam Types
     * (and @tparam FirstType). This Variant can hold only one of the Types at
     * any one time, and the previously held value will be destroyed before a
     * new one is created and held.
     * This will default construct the @tparam FirstType with the default
     * constructor.
     */
    template<typename FirstType, typename... Types>
    class Variant {
        enum : size_t {
            size = std::max({ sizeof(FirstType), sizeof(Types)... })
        };

        detail::VariantStorage<size> storage { };

    public:
        constexpr auto data() noexcept -> void* {
            return storage.data;
        }

        [[nodiscard]]
        constexpr auto index() const noexcept -> int {
            return storage.index;
        }

        constexpr Variant() noexcept {
            auto* pointer = static_cast<FirstType*>(data());
            std::construct_at(pointer);
        }

        template<class Type>
        explicit constexpr Variant(Type initialValue) noexcept:
            storage { .index = VariantIndex<0, Type, FirstType, Types...>().index } {
            auto* pointer = static_cast<Type*>(data());
            std::construct_at(pointer, initialValue);
        }

        ~Variant() {
            detail::destroyLinear<0, FirstType, Types...>(index(), data());
        }

        /**
         * This replaces the held Variant Type with a new value of type
         * @tparam Type. The Previous Type is found and used to destroy the
         * current value before constructing the new value.
         * @param args are passed to the types constructor as needed.
         * @return a reference to the newly held type.
         */
        template<class Type, class... Args>
        constexpr auto emplace(Args&& ... args) -> Type& {
            // Search the Type pack and call the Type destructor.
            detail::destroyLinear<0, FirstType, Types...>(index(), data());

            auto* pointer = static_cast<Type*>(data());
            std::construct_at(pointer, args...);

            storage.index = VariantIndex<0, Type, FirstType, Types...>().index;
            return *pointer;
        }
    };
}


#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_VARIANT_VARIANT_H
