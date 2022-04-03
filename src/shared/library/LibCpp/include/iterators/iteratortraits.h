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

//
// Created by david on 03/04/2022.
//

#ifndef HEPHAISTOS_ITERATORTRAITS_H
#define HEPHAISTOS_ITERATORTRAITS_H

#include <cstddef>
#include <type_traits>

namespace std {

    /**
     * Iterator traits defines a set of Types that an @tparam Iterator Type needs to provided to be
     * a valid iterator.
     */
    template<class Iterator>
    struct iteratorTraits {
        using valueType = typename Iterator::valueType;
        using differenceType = typename Iterator::differenceType;
        using pointer = typename Iterator::pointer;
        using reference = typename Iterator::reference;
    };

    /**
     * This is a specialism of Iterator traits for pointer types. This defines the specific
     * Types for a pointer as it cannot be added to the pointer like in a class or struct.
     */
    template<class Iterator>
    struct iteratorTraits<Iterator*> {
        using valueType = Iterator;
        using differenceType = ptrdiff_t;
        using pointer = Iterator *;
        using reference = Iterator &;
    };

    /**
     * De-referenceable defines that @tparam Type can be de-referenced, and is not todo: void.
     */
    template<class Type>
    concept Dereferenceable = requires(Type type) {
        *type;
    };

    /**
     * iterator Value Type is a shorthand concept for retrieving the value type of an
     * @tparam Iterator.
     */
    template<class Iterator>
    using iteratorValueType =
            typename std::iteratorTraits<Iterator>::valueType; // todo: need to be std::remove_cvref<...

    /**
     * iterator Reference Type computes the reference type for a given @tparam Iterator.
     */
    template< Dereferenceable Iterator>
    using iteratorReferenceType = decltype(*std::declval<Iterator&>());

    /**
     * iterator Difference Type is a shorthand concept for retrieving the value type of an
     * @tparam Iterator.
     */
    template<class Iterator>
    using iteratorDifferenceType =
            typename std::iteratorTraits<Iterator>::differenceType; // todo: need to be std::remove_cvref<...
}

#endif //HEPHAISTOS_ITERATORTRAITS_H
