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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_INT_FORMATTER_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_INT_FORMATTER_H

#include "formatter.h"
#include <limits>
#include <type_traits>

namespace std {

    /**
     * Concept denotes that a @tparam Type can be divided.
     */
    template<class Type>
    concept dividable = std::integral<Type>
                        && requires(const Type a, const Type b) { a / b; };

    /**
     * Concept denotes that a @tparam Type can have its modulus taken.
     */
    template<class Type>
    concept modulusable = std::integral<Type>
                          && requires(const Type a, const Type b) { a % b; };

    /**
     * Concept denotes that a @tparam Type can be formatted by the
     * Int formatter.
     */
    template<class Type>
    concept formatableIntegral = dividable<Type> && modulusable<Type>;

    namespace detail {

        // Maximum length of a digit equal to 9 in binary: 1001
        constexpr static int DIGIT_OUTPUT_SIZE = 4;

        /**
         * This takes the @param value and splits it into its individual digits by recursively
         * dividing it by the @param base and taking the individual digit from the modulus from the
         * @param base.
         * The individual digit is added to the output using std::toChars. The maximum size of the
         * output is 4 characters as seen in DIGIT_OUTPUT_SIZE.
         * The behaviour is undefined if the output container is not large enough.
         *
         * @return an iterator to the end of the outputted integer.
         */
        template<class OutputIterator, formatableIntegral Type>
        auto formatInteger(OutputIterator iterator, Type value, auto base) -> OutputIterator {
            auto reduction = value / base;

            OutputIterator outputIterator = iterator;
            if (reduction == 0) {
                outputIterator = iterator;
            } else {
                outputIterator = formatInteger(iterator, reduction, base);
            }

            auto digit = value % base;

            // use to chars to convert to string
            auto buffer = std::Array<char, DIGIT_OUTPUT_SIZE> { };
            auto result = std::toChars(buffer.begin(), buffer.end(), digit, static_cast<int>(base));

            std::forEach(
                buffer.begin(), result, [&outputIterator](char character) {
                    *outputIterator++ = character;
                }
            );

            return outputIterator;
        }
    }

    /**
     * This specializes Formatter for integral types.
     * i.e. int, long, long long, unsigned int, etc...
     * This will take an integer, break it into digits, and output each digit
     * individually.
     */
    template<std::integral Type>
    struct Formatter<Type> {

        enum class OutputType : uint32_t {
            DECIMAL = 10,
            HEX = 16,
            BINARY = 2
        };

        OutputType outputType = OutputType::DECIMAL;

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                switch (*iterator) {
                    case 'x':
                        outputType = OutputType::HEX;
                        break;
                    case 'b':
                        outputType = OutputType::BINARY;
                        break;
                }
                ++iterator;
            }

            return iterator;
        }

        auto format(auto& integer, auto& state) {
            auto output = state.out();

            if (outputType == OutputType::HEX) {
                *output++ = '0';
                *output++ = 'x';
            }

            if (outputType == OutputType::BINARY) {
                *output++ = '0';
                *output++ = 'b';
            }

            const auto base = static_cast<std::underlying_type_t<OutputType>>(outputType);
            return detail::formatInteger(output, integer, static_cast<std::remove_cvref_t<decltype(integer)>>(base));
        }
    };
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_FORMAT_INT_FORMATTER_H
