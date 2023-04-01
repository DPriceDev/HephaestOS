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

#include "algorithm.h"
#include "expected.h"
#include "span.h"
#include "system_error.h"

namespace std {

    /**
     * This method takes specifically an integral @param value
     * i.e. int, long, long long, unsigned int, and outputs it to a char string
     * starting from @param first and ending at @param last.
     * The base is defaulted to decimal 10, but can be changed to a range of
     * 2 to 36 to output in a different base.
     */
    constexpr char* toChars(char* first, char* last, std::integral auto value, int base = 10) {
        const char* characters = "0123456789abcdefghijklmnopqrstuvwxyz";

        if constexpr (std::is_signed_v<decltype(value)>) {
            if (value < 0) {
                *first++ = '-';
                value *= -1;
            }
        }

        auto initialFirst = first;
        decltype(value) remainder;
        do {
            remainder = value % static_cast<decltype(value)>(base);
            value = value / static_cast<decltype(value)>(base);
            *first++ = characters[remainder];
        } while (value != 0 && first != last);

        std::reverse(initialFirst, first);

        return first;
    }

    /**
     * This method takes specifically a floating point @param value
     * i.e. float, double, long double, and outputs it to a char string
     * starting from @param first and ending at @param last.
     * This will output the entire length of the number.
     */
    constexpr char* toChars(char* first, char* last, std::floating_point auto value) {
        long wholeNumber = static_cast<long>(value);
        auto* next = toChars(first, last, wholeNumber);
        *next++ = '.';

        auto decimalNumber = value - static_cast<decltype(value)>(wholeNumber);

        auto remainder = decimalNumber;
        while (remainder != 0) {
            decimalNumber *= 10;
            const auto whole = static_cast<unsigned long long>(decimalNumber);
            remainder = decimalNumber - static_cast<decltype(value)>(whole);
        }

        // todo: Some sort of rounding here?

        return toChars(next, last, static_cast<unsigned long long>(decimalNumber));
    }

    /**
     * This method will take a string in the range of @param first to  @param last
     * and convert it to an integer type i.e. int, long, unsigned int.
     *
     * The given @param base will change how the characters in the string are
     * interpreted, and will construct the integer result from the correct base.
     */
    template<std::integral Type>
    constexpr std::Optional<Type> fromChars(const char* first, const char* last, std::size_t base = 10) {
        auto view = std::StringView(first, static_cast<std::size_t>(last - first));

        std::size_t running = 0;
        std::size_t power = 1;
        std::forEach(view.rbegin(), view.rend(), [&](auto& character) {
            running += (Type(character) - 48) * power;// todo: Handle errors / overflow
            power *= base;// todo: handle int is too big / overflow?
        });

        return std::Optional<std::size_t>(running);
    }
}// namespace std

#endif// HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_CHARCONV_H