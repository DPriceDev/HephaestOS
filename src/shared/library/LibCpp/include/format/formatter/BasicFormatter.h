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
#ifndef HEPHAISTOS_BASIC_FORMATTER_H
#define HEPHAISTOS_BASIC_FORMATTER_H

#include "format/parse_state.h"
#include "format/format_state.h"

namespace std {

    /**
     * TODO: Comment
     * @tparam Formatter
     * @tparam Arg
     */
    template<class Formatter, class Arg>
    concept BasicFormatter =
    std::is_default_constructible_v<Formatter>
    && std::is_copy_constructible_v<Formatter>
    && std::is_copy_assignable_v<Formatter>
    && std::is_destructible_v<Formatter>
    && std::is_swappable_v<Formatter>
    && requires (Formatter formatter, std::ParseState state) {
        { formatter.parse(state) } -> std::same_as<ParseState::iterator>;
    };
    // todo: Need to constrain format
//        && requires (Formatter formatter, Arg arg, std::FormatState state) {
//            { formatter.format(arg, state) } -> std::same_as<std::FormatState::iterator>;
//        };
}

#endif // HEPHAISTOS_BASIC_FORMATTER_H