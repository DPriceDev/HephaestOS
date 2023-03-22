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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_REVERSE_ITERATOR_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_REVERSE_ITERATOR_H

#include "iterator_operations.h"

namespace std {

    /**
     * Reverse Iterator defines an iterator that will go to the previous element when the
     * iterator is incremented.
     */
    template<std::bidirectionalIterator Iterator>
    class reverseIterator {
        Iterator iterator_ {};

      public:
        using iteratorType = Iterator;
        using valueType = std::iteratorValueType<Iterator>;
        using differenceType = std::iteratorDifferenceType<Iterator>;
        using pointer = typename std::iteratorTraits<Iterator>::pointer;
        using reference = std::iteratorReferenceType<Iterator>;

        /**
         * Constructs a reverse iterator from a given @param iterator.
         */
        constexpr explicit reverseIterator(Iterator iterator) : iterator_(iterator) {}

        constexpr reference operator*() const {
            auto temp = iterator_;
            return *std::prev(temp);
        }

        constexpr pointer operator->() const { return std::prev(iterator_); }

        constexpr auto& operator++() {
            --iterator_;
            return *this;
        }

        auto& operator++(int) {
            --iterator_;
            return *this;
        }

        constexpr friend bool operator!=(reverseIterator<Iterator> first, reverseIterator<Iterator> second) {
            return first.iterator_ != second.iterator_;
        }
    };

}// namespace std

#endif// HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_REVERSE_ITERATOR_H
