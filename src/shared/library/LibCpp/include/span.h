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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_SPAN_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_SPAN_H

#include <concepts>
#include "iterator.h"

namespace std {

    /**
     *
     * @tparam Type
     * @tparam Extent
     */
    template<class Type> requires contiguousIterator<Type*>
    class Span {
    public:
        using elementType = Type;
        using valueType = typename std::remove_cv<elementType>::type;
        using pointer = Type *;
        using differenceType = std::ptrdiff_t;
        using constPointer = const Type *;
        using reference = Type &;
        using constReference = const Type &;
        using iterator = valueType *;

    };
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_SPAN_H