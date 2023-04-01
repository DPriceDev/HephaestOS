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

#ifndef HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_BASIC_FORMATTER_H
#define HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_BASIC_FORMATTER_H

#include "format/format_state.h"
#include "format/parse_state.h"

namespace std {

    /**
     * This concept defines what a basic formatter is, apart from being movable,
     * The most important attributes of a formatter is that it has the format
     * and parse methods.
     * The parse method will take the parse state, and return an iterator to the
     * end of the parse field '{...}' if successful.
     * The format method will take the Arg to format, and the format state, and
     * return an iterator to the end of the outputted value.
     */
    template<class Formatter, class Arg>
    concept BasicFormatter = std::is_default_constructible_v<Formatter> && std::is_copy_constructible_v<Formatter>
                          && std::is_copy_assignable_v<Formatter> && std::is_destructible_v<Formatter>
                          && std::is_swappable_v<Formatter> && requires(Formatter formatter, std::ParseState state) {
                                 { formatter.parse(state) } -> std::same_as<ParseState::iterator>;
                             };
    // todo: Need to constrain format
    //        && requires (Formatter formatter, Arg arg, std::FormatState state) {
    //            { formatter.format(arg, state) } -> std::same_as<std::FormatState::iterator>;
    //        };
}// namespace std

#endif// HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_BASIC_FORMATTER_H