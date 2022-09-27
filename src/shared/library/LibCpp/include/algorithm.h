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
#include <initializer_list>

namespace std {

    template<std::inputIterator Iterator, class UnaryFunction>
    constexpr UnaryFunction forEach(Iterator first, Iterator last, UnaryFunction function) {
        for (; first != last; ++first) {
            function(*first);
        }
        return function;
    }

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
        class BinaryOperation
    >
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

    template<forwardIterator Iterator, class Comparator>
    constexpr Iterator maxElement(Iterator first, Iterator last, Comparator comparator) {
        if (first == last) {
            return last;
        }

        Iterator largest = first;
        ++first;
        for (; first != last; ++first) {
            if (comparator(*largest, *first)) {
                largest = first;
            }
        }
        return largest;
    }

    template<forwardIterator Iterator>
    constexpr Iterator maxElement(Iterator first, Iterator last) {
        if (first == last) return last;

        Iterator largest = first;
        ++first;
        for (; first != last; ++first) {
            if (*largest < *first) {
                largest = first;
            }
        }
        return largest;
    }

    template<class Type>
    constexpr auto max(const Type& first, const Type& second) -> const Type& {
        return first <= second ? first : second;
    }

    template<class Type>
    constexpr Type max(std::initializer_list<Type> initializerList) {
        return *std::maxElement(initializerList.begin(), initializerList.end());
    }

    template<inputIterator InputIterator, class Type>
    constexpr InputIterator find(InputIterator first, InputIterator last, const Type& value) {
        for (; first != last; ++first) {
            if (*first == value) {
                return first;
            }
        }
        return last;
    }

    template<inputIterator InputIterator, class UnaryPredicate>
    constexpr InputIterator findIf(InputIterator first, InputIterator last, const UnaryPredicate predicate) {
        for (; first != last; ++first) {
            if (predicate(*first)) {
                return first;
            }
        }
        return last;
    }

    template<inputIterator InputIterator, class OutputIterator>
    constexpr OutputIterator copy(InputIterator first, InputIterator last, OutputIterator output) {
        for (; first != last; ++first, ++output) {
            *output = *first;
        }
        return output;
    }

    template<forwardIterator IteratorA, forwardIterator IteratorB>
    constexpr void iteratorSwap(IteratorA a, IteratorB b) {
        std::swap(*a, *b);
    }

    template<bidirectionalIterator Iterator>
    constexpr void reverse(Iterator first, Iterator last) {
        while ((first != last) && (first != --last)) {
            std::iteratorSwap(first++, last);
        }
    }
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ALGORITHMS_H
