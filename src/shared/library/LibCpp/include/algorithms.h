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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ALGORITHMS_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ALGORITHMS_H

#include "iterator.h"

namespace std {

    /**
     * todo: comment
     */
    template<std::inputIterator Iterator, class UnaryFunction>
    constexpr UnaryFunction forEach(Iterator first, Iterator last, UnaryFunction function)
    {
        for(; first != last; ++first) {
            function(*first);
        }
        return function;
    }

    // todo: implement when ExecutionPolicy exists
    // template< class ExecutionPolicy, class ForwardIt, class UnaryFunction2 >
    // void for_each( ExecutionPolicy&& policy, ForwardIt first, ForwardIt last, UnaryFunction2 f );

    /**
     *
     * @tparam Iterator
     * @tparam OutputIterator
     * @tparam UnaryOperation
     */
    template<inputIterator Iterator, class Type, outputIterator<Type> OutputIterator, class UnaryOperation>
    OutputIterator transform(
            Iterator first,
            Iterator last,
            OutputIterator outFirst,
            UnaryOperation operation
    ) {
        while (first != last) {
            *outFirst++ = operation(*first++);
        }
        return outFirst;
    }

    template<
            inputIterator IteratorA,
            inputIterator IteratorB,
            class Type,
            outputIterator<Type> OutputIterator,
            class BinaryOperation>
    OutputIterator transform(
            IteratorA firstA,
            IteratorA lastA,
            IteratorB firstB,
            OutputIterator outFirst,
            BinaryOperation operation
    ) {
        while (firstA != lastA) {
            *outFirst++ = operation(*firstA++, *firstB++);
        }
        return outFirst;
    }

}

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ALGORITHMS_H
