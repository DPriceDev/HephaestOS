// Copyright (C) 2023 David Price - All Rights Reserved
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

#ifndef HEPHAEST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_ITERATOR_OPERATIONS_H
#define HEPHAEST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_ITERATOR_OPERATIONS_H

#include "iterator_traits.h"
#include "iterators.h"

namespace std {

    namespace detail {

        /**
         * todo:
         */
        template<std::inputIterator Iterator>
        constexpr void advance(Iterator& it, typename std::iteratorDifferenceType<Iterator> count) {
            while (count > 0) {
                --count;
                ++it;
            }
        }

        /**
         * todo:
         */
        template<std::bidirectionalIterator Iterator>
        constexpr void advance(Iterator& it, typename std::iteratorDifferenceType<Iterator> count) {
            while (count > 0) {
                --count;
                ++it;
            }
            while (count < 0) {
                ++count;
                --it;
            }
        }

        /**
         * todo:
         */
        template<std::randomAccessIterator Iterator>
        constexpr void advance(Iterator& iterator, typename std::iteratorDifferenceType<Iterator> count) {
            iterator += count;
        }
    }// namespace detail

    /**
     * todo:
     */
    template<inputOrOutputIterator Iterator, class Distance>
    constexpr void advance(Iterator& iterator, Distance distance) {
        detail::advance(iterator, distance);
    }

    /**
     * todo:
     */
    template<std::inputIterator Iterator>
    constexpr Iterator next(Iterator iterator, typename std::iteratorDifferenceType<Iterator> count = 1) {
        std::advance(iterator, count);
        return iterator;
    }

    /**
     * todo:
     */
    template<std::bidirectionalIterator Iterator>
    constexpr Iterator prev(Iterator& iterator, typename std::iteratorDifferenceType<Iterator> count = 1) {
        std::advance(iterator, -count);
        return iterator;
    }
}// namespace std

#endif// HEPHAEST_OS_SHARED_LIBRARY_LIB_CPP_ITERATORS_ITERATOR_OPERATIONS_H
