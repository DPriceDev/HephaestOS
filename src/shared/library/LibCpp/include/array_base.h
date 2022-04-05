/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaistOS.
 *
 * HephaistOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaistOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaistOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_ARRAY_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_ARRAY_H

#include <cstdint>
#include "iterator.h"
#include "algorithms.h"

namespace std::detail {

    template<class Type, std::size_t Length>
    struct Array {
        Type array[Length];

        // Container Definitions
        using elementType = Type;
        using valueType = elementType;
        using sizeType = typename std::size_t;
        using differenceType = std::ptrdiff_t;
        using pointer = valueType *;
        using constPointer = const valueType *;
        using reference = valueType &;
        using constReference = const valueType &;
        using iterator = valueType *;
        using constIterator = const valueType *;
        using reverseIterator = std::reverseIterator<iterator>;
        using constReverseIterator = std::reverseIterator<constIterator>;

        // Element Access
        constexpr auto operator[](sizeType index) -> reference {
            return array[index];
        }

        constexpr auto operator[](sizeType index) const -> constReference {
            return array[index];
        }

        constexpr auto data() noexcept -> pointer {
            return array;
        }

        constexpr auto data() const noexcept -> constPointer {
            return array;
        }

        constexpr auto front() -> reference {
            return *data();
        }

        constexpr auto front() const -> constReference {
            return *data();
        }

        constexpr auto back() -> reference {
            return *(data() + size());
        }

        constexpr auto back() const -> constReference {
            return *(data() + size());
        }

        // Iterators
        constexpr auto begin() noexcept -> iterator {
            return data();
        }

        constexpr auto begin() const noexcept -> constIterator {
            return data();
        }

        constexpr auto cbegin() const noexcept -> constIterator {
            return data();
        }

        constexpr auto end() noexcept -> iterator {
            return data() + size();
        }

        constexpr auto end() const noexcept -> constIterator {
            return data() + size();
        }

        constexpr auto cend() const noexcept -> constIterator {
            return data() + size();
        }

        constexpr auto rbegin() noexcept -> reverseIterator {
            return constReverseIterator(data() + size());
        }

        constexpr auto rbegin() const noexcept -> constReverseIterator {
            return constReverseIterator(data() + size());
        }

        constexpr auto crbegin() const noexcept -> constReverseIterator {
            return constReverseIterator(data() + size());
        }

        constexpr auto rend() noexcept -> reverseIterator {
            return reverseIterator(data());
        }

        constexpr auto rend() const noexcept -> constReverseIterator {
            return constReverseIterator(data());
        }

        constexpr auto crend() const noexcept -> constReverseIterator {
            return constReverseIterator(data());
        }

        // Capacity
        [[nodiscard]]
        constexpr auto size() const noexcept -> sizeType {
            return Length;
        }

        [[nodiscard]]
        constexpr auto lastIndex() const noexcept -> sizeType {
            return Length > 0 ? Length - 1 : 0;
        }

        [[nodiscard]]
        constexpr bool empty() const noexcept {
            return size() == 0;
        }

        // Operations
        constexpr void fill(const Type& value) {
            std::forEach(begin(), end(), [value] (auto & element) {
                element = value;
            });
        }


    };
}
#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_ARRAY_H
