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

#ifndef HEPHAEST_OS_ARRAY_H
#define HEPHAEST_OS_ARRAY_H

#include "array_base.h"
#include "functional.h"
#include "optional.h"
#include <cstdint>

namespace std {

    template<typename Type, std::size_t Length>
    struct Array : public detail::Array<Type, Length> {

        [[nodiscard]] constexpr auto at(typename Array<Type, Length>::sizeType index)
            -> std::Optional<std::ReferenceWrapper<Type>> {
            if (index < 0 && index >= Length) {
                return std::nullOptional;
            }
            return std::Optional<std::ReferenceWrapper<Type>>(this->operator[](index));
        }

        [[nodiscard]] constexpr auto at(typename Array<Type, Length>::sizeType index) const
            -> const std::Optional<std::ReferenceWrapper<Type>> {
            if (index < 0 && index >= Length) {
                return std::nullOptional;
            }
            return std::Optional<std::ReferenceWrapper<Type>>(this->operator[](index));
        }

        // todo: constexpr auto swap(Array<Type, Length>& other) noexcept;
    };
}// namespace std

#endif// HEPHAEST_OS_ARRAY_H
