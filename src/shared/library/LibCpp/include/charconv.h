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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_CHARCONV_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_CHARCONV_H

#include "result.h"
#include "system_error.h"
#include "span.h"
#include "algorithms.h"

namespace std {

    constexpr char* toChars(
            char* first,
            char* last,
            std::integral auto value,
            int base = 10
    ) {
        const char* characters = "0123456789abcdefghijklmnopqrstuvwxyz";

        if (value < 0) {
            *first++ = '-';
            value *= -1;
        }

        auto initialFirst = first;
        decltype(value) remainder;
        do {
            remainder = value % base;
            value = value / base;
            *first++ = characters[remainder];
        } while(value != 0 && first != last);

        std::reverse(initialFirst, first);

        return first;
    }

    constexpr char* toChars(
        char* first,
        char* last,
        std::floating_point auto value
    ) {
        long wholeNumber = static_cast<long>(value);
        auto* next = toChars(first, last, wholeNumber);
        *next++ = '.';

        auto decimalNumber = value - wholeNumber;

        auto remainder = decimalNumber;
        while(remainder != 0.0) {
            decimalNumber *= 10;
            remainder = decimalNumber - static_cast<unsigned long long>(decimalNumber);
        }

        // todo: Some sort of rounding here?

        return toChars(next, last, static_cast<unsigned long long>(decimalNumber));
    }

    /**
     * Int specialization
     * @param first
     * @param last
     * @param base
     * @return
     */
    template<std::integral Type>
    constexpr std::Result<Type, Error> fromChars(
            const char* first,
            const char* last,
            int base = 10
    ) {
        auto view = std::StringView(first, last - first);

        auto running = 0;
        auto power = 1;
        std::forEach(view.rbegin(), view.rend(), [&] (auto & character) {
            running += (Type(character) - 48) * power; // todo: Handle errors / overflow
            power *= base; // todo: handle int is too big / overflow?
        });

        return std::Result<std::size_t, Error>::success(running);
    }
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_CHARCONV_H