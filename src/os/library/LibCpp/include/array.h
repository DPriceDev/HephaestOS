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

#ifndef HEPHAISTOS_ARRAY_H
#define HEPHAISTOS_ARRAY_H

#include <cstdint>
#include "array_base.h"
#include "result.h"

namespace std {

    template<typename Type, std::size_t Length>
    struct Array : public detail::Array<Type, Length> {

        [[nodiscard]]
        constexpr auto at(typename Array<Type, Length>::sizeType index) -> std::Result<Type&> {
            if (index >= 0 && index < Length) {
                return std::Result<Type&>::success(this->operator[](index));
            }
            return std::Result<Type&>::failure();
        }

        [[nodiscard]]
        constexpr auto at(typename Array<Type, Length>::sizeType index) const -> const std::Result<Type&> {
            if (index >= 0 && index < Length) {
                return std::Result<Type&>::success(this->operator[](index));
            }
            return std::Result<Type&>::failure();
        }

        // todo: constexpr auto swap(Array<Type, Length>& other) noexcept;
    };
}

#endif //HEPHAISTOS_ARRAY_H
