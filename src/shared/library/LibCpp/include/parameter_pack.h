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

#ifndef VARIANT_VARIANT_PARAMETER_H
#define VARIANT_VARIANT_PARAMETER_H

namespace std {

    /**
     * Parameter Pack allows a set of variadic @tparam Parameters to be passed to a function
     * without it interfering or picking up types from another set of variadic parameters.
     */
    template<class... Parameters>
    struct ParameterPack {};

    /**
     * Parameter Type allows a given @tparam Type to be passed to a function as
     * a parameter without interfering with a variadic parameter pack. It also
     * allows the Type to be defined out of order.
     */
    template<class Type>
    struct ParameterType {};

}// namespace std

#endif// VARIANT_VARIANT_PARAMETER_H
