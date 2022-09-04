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

#ifndef HEPHAISTOS_FORMATTER_H
#define HEPHAISTOS_FORMATTER_H

namespace std {

    // todo: can this be a concept that requires something?
    // todo: Do we need to add functions to extend to this?
    // todo: Probably need a concept as well as this and the concept is used at calling points?
    template<class Type, class CharacterType = char>
    struct Formatter;

}


#endif //HEPHAISTOS_FORMATTER_H
