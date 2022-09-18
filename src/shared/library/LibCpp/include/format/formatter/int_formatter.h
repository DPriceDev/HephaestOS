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

// TODO: Format Header
#ifndef HEPHAISTOS_INT_FORMATTER_H
#define HEPHAISTOS_INT_FORMATTER_H

#include <limits>

#include "formatter.h"
#include "variant.h"

namespace std {

    /**
     * TODO: Comment
     * @tparam Type
     */
    template<class Type>
    concept dividable = std::integral<Type>
            && requires(const Type a, const Type b) { a / b; };

    /**
     * TODO: Commment
     * @tparam Type
     */
    template<class Type>
    concept modulusable = std::integral<Type>
                        && requires(const Type a, const Type b) { a % b; };

    /**
     * TODO: Comment
     * @tparam Type
     */
    template<class Type>
    concept formatableIntegral = dividable<Type> && modulusable<Type>;

    /**
     * TODO: Comment
     * @tparam OutputIterator
     * @tparam Type
     * @param iterator
     * @param value
     * @param base
     * @return
     */
    template<class OutputIterator, formatableIntegral Type>
    auto formatDigit(OutputIterator iterator, Type value, Type base = 10) -> OutputIterator {
        auto reduction = value / base;

        OutputIterator outputIterator;
        if (reduction == 0) {
            outputIterator = iterator;
        } else {
            outputIterator = formatDigit(iterator, reduction);
        }

        auto digit = value % base;

        // use to chars to convert to string
        std::toChars(outputIterator, outputIterator + 2, digit);

        return ++outputIterator;
    }

    /**
     * Int specification
     * TODO: Comment
     */
    template<std::integral Type>
    struct Formatter<Type> {

        constexpr auto parse(auto &state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(auto &integer, auto &state) {
            auto output = state.out();
            return formatDigit(output, integer);
        }
    };
}

#endif // HEPHAISTOS_INT_FORMATTER_H
