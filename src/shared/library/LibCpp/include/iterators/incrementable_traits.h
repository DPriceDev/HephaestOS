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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_ITERATORS_INCREMENTABLE_TRAITS_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_ITERATORS_INCREMENTABLE_TRAITS_H

#include <type_traits>
#include <concepts>

// TODO: Comment or remove
namespace std {

    template<class Iterator>
    struct incrementableTraits { };

    template<class Iterator>
    requires std::is_object_v<Iterator>
    struct incrementableTraits<Iterator*> {
        using differenceType = std::ptrdiff_t;
    };

    template<class Iterator>
    struct incrementableTraits<const Iterator> : incrementableTraits<Iterator> {
        using differenceType = std::ptrdiff_t;
    };

    template<class Iterator >
    requires requires { typename Iterator::difference_type; }
    struct incrementableTraits<Iterator> {
        using differenceType = typename Iterator::difference_type;
    };

    template<class Iterator>
    requires (!requires { typename Iterator::difference_type; }) &&
             requires(const Iterator& a, const Iterator& b) { { a - b } -> std::integral; }
    struct incrementableTraits<Iterator> {
        using differenceType = std::make_signed_t<decltype(std::declval<Iterator>() - std::declval<Iterator>())>;
    };

}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_ITERATORS_INCREMENTABLE_TRAITS_H
