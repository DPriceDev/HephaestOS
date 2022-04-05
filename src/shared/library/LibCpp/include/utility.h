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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_UTILITY_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_UTILITY_H

#include <type_traits>

namespace std {

    template< class Type>
    constexpr Type&& forward(std::remove_reference_t<Type>& type) noexcept {
        return static_cast<Type&&>(type);
    }

    template< class Type>
    constexpr Type&& forward(std::remove_reference_t<Type>&& type) noexcept {
        return static_cast<Type&&>(type);
    }
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_UTILITY_H
