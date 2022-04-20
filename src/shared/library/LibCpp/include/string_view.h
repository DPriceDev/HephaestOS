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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_VIEW_H
#define HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_VIEW_H

#include "compare"
#include "limits"
#include "iterator.h"
#include "string.h"
#include "result.h"

namespace std {
    template<class CharacterType, class Traits = std::CharacterTraits<CharacterType>>
    class BaseStringView {

    public:
        using traitsType = Traits;
        using valueType = CharacterType;
        using pointer = CharacterType*;
        using constPointer = const CharacterType*;
        using reference = CharacterType&;
        using constReference = const CharacterType&;
        using constIterator = const CharacterType*;
        using iterator = constIterator;
        using constReverseIterator = std::reverseIterator<constIterator>;
        using reverseIterator = std::reverseIterator<constIterator>;
        using sizeType = std::size_t;
        using differenceType = std::ptrdiff_t;

        // Constructors

        constexpr BaseStringView() noexcept : stringStart(nullptr), stringEnd(nullptr) { }

        constexpr BaseStringView(const CharacterType* string, sizeType count) :
            stringStart(string),
            stringEnd(string + count) { }

        constexpr BaseStringView(const CharacterType* string) :
                stringStart(string),
                stringEnd(string + Traits::length(string)) { }

        template<contiguousIterator Iterator, sizedSentinelFor<Iterator> End>
        constexpr BaseStringView(Iterator first, End last) : stringStart(first), stringEnd(last) { }

        // Iterators
        constexpr auto begin() const noexcept -> constIterator {
            return stringStart;
        }

        constexpr auto cbegin() const noexcept -> constIterator {
            return stringStart;
        }

        constexpr auto end() const noexcept -> constIterator {
            return stringEnd;
        }

        constexpr auto cend() const noexcept -> constIterator {
            return stringEnd;
        }

        constexpr auto rbegin() const noexcept -> constReverseIterator {
            return std::reverseIterator(stringEnd);
        }

        constexpr auto crbegin() const noexcept -> constReverseIterator {
            return std::reverseIterator(stringEnd);
        }

        constexpr auto rend() const noexcept -> constReverseIterator {
            return std::reverseIterator(stringStart);
        }

        constexpr auto crend() const noexcept -> constReverseIterator {
            return std::reverseIterator(stringEnd);
        }

        // Element Access
        constexpr auto operator[](sizeType index) const -> constReference {
            return *(data() + index);
        }

        // todo: Move to implementation? or wrap later on? make protected and expose in child?
        constexpr std::Result<constReference> at(sizeType index) const {
            if(index >= 0 && index < size()) {
                return std::Result<constReference>::success(this->operator[](index));
            }
            return std::Result<constReference>::failure();
        }

        constexpr auto front() const -> constReference {
            return *stringStart;
        }

        constexpr auto back() const -> constReference {
            return *stringEnd;
        }

        constexpr auto data() const noexcept -> constPointer {
            return stringStart;
        }

        // Capacity
        [[nodiscard]] constexpr sizeType size() const noexcept {
            return stringStart - stringEnd;
        }

        [[nodiscard]] constexpr sizeType length() const noexcept {
            return stringStart - stringEnd;
        }

        [[nodiscard]] constexpr sizeType maxSize() const noexcept {
            return std::numeric_limits<CharacterType>::max();
        }

        [[nodiscard]] constexpr bool empty() const noexcept {
            return (stringStart - stringEnd) <= 0;
        }

        // Modifiers
        // todo as required

        // Operations
        // todo as required

    private:
        constIterator stringStart;
        constIterator stringEnd;
    };


    using StringView = BaseStringView<char>;

    template<class Type>
    concept convertableToStringView = requires(Type* type) {
        std::BaseStringView<Type>(type);
    };

}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_VIEW_H
