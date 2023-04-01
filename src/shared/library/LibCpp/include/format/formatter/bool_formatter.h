// Copyright (C) 2022 David Price - All Rights Reserved
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

#ifndef HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_BOOL_FORMATTER_H
#define HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_BOOL_FORMATTER_H

#include "algorithm.h"
#include "formatter.h"
#include "string_view.h"

namespace std {

    /**
     * Specializes the Formatter for bool types.
     * Will currently format to either 'True' or 'False'.
     */
    template<>
    struct Formatter<bool> {

        constexpr auto parse(auto& state) {
            auto iterator { state.begin() };
            const auto end { state.end() };

            while (iterator != end && *iterator != '}') {
                // todo: Parse Formatter Arguments
                ++iterator;
            }

            return iterator;
        }

        auto format(const bool& boolean, auto& state) {
            auto output = state.out();

            if (boolean) {
                return std::copy(trueView.begin(), trueView.end(), output);
            }

            return std::copy(falseView.begin(), falseView.end(), output);
        }

      private:
        constexpr static auto trueView = std::StringView { "True" };
        constexpr static auto falseView = std::StringView { "False" };
    };
}// namespace std

#endif// HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_BOOL_FORMATTER_H
