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

#ifndef HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMATTER_H
#define HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMATTER_H

namespace std {

    /**
     * This is the base definition of the formatter used by std::format.
     * This is specialised for all standard types defined in format arguments.
     * This can be specialized for custom types for use with std::format.
     *
     * @tparam Type is the type of the value to be formatted.
     * @tparam CharacterType - is the type of the container the value will be formatted to.
     */
    template<class Type, class CharacterType = char>
    struct Formatter;
}// namespace std

#endif// HEPHAEST_OS_SHARED_LIBRARY_CPP_FORMAT_FORMATTER_H
