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
#include "string"
#include "result.h"
#include "algorithm.h"

namespace std {
    template<class CharacterType, class Traits = std::CharacterTraits<CharacterType>>
    class BaseStringView {

    public:
        using TraitsType = Traits;
        using ValueType = CharacterType;
        using Pointer = CharacterType*;
        using ConstPointer = const CharacterType*;
        using Reference = CharacterType&;
        using ConstReference = const CharacterType&;
        using ConstIterator = const CharacterType*;
        using Iterator = ConstIterator;
        using ConstReverseIterator = std::reverseIterator<ConstIterator>;
        using ReverseIterator = std::reverseIterator<ConstIterator>;
        using SizeType = std::size_t;
        using DifferenceType = std::ptrdiff_t;

        // Constructors

        constexpr BaseStringView() noexcept: start_(nullptr), end_(nullptr) { }

        constexpr BaseStringView(const CharacterType* string, SizeType count) :
            start_(string),
            end_(string + count) { }

        constexpr BaseStringView(const CharacterType* string) :
            start_(string),
            end_(string + Traits::length(string)) { }

        template<contiguousIterator Iterator, sizedSentinelFor<Iterator> End>
        constexpr BaseStringView(Iterator first, End last) : start_(first), end_(last) { }

        // Iterators
        constexpr auto begin() const noexcept -> ConstIterator {
            return start_;
        }

        constexpr auto cbegin() const noexcept -> ConstIterator {
            return start_;
        }

        constexpr auto end() const noexcept -> ConstIterator {
            return end_;
        }

        constexpr auto cend() const noexcept -> ConstIterator {
            return end_;
        }

        constexpr auto rbegin() const noexcept -> ConstReverseIterator {
            return std::reverseIterator(end_);
        }

        constexpr auto crbegin() const noexcept -> ConstReverseIterator {
            return std::reverseIterator(end_);
        }

        constexpr auto rend() const noexcept -> ConstReverseIterator {
            return std::reverseIterator(start_);
        }

        constexpr auto crend() const noexcept -> ConstReverseIterator {
            return std::reverseIterator(end_);
        }

        // Element Access
        constexpr auto operator[](SizeType index) const -> ConstReference {
            return *(data() + index);
        }

        // todo: Move to implementation? or wrap later on? make protected and expose in child?
        constexpr std::Result<ConstReference> at(SizeType index) const {
            if (index >= 0 && index < size()) {
                return std::Result<ConstReference>::success(this->operator[](index));
            }
            return std::Result<ConstReference>::failure();
        }

        constexpr auto front() const -> ConstReference {
            return *start_;
        }

        constexpr auto back() const -> ConstReference {
            return *end_;
        }

        constexpr auto data() const noexcept -> ConstPointer {
            return start_;
        }

        // Capacity
        [[nodiscard]] constexpr SizeType size() const noexcept {
            return end_ - start_;
        }

        [[nodiscard]] constexpr SizeType length() const noexcept {
            return static_cast<SizeType>(end_ - start_);
        }

        [[nodiscard]] constexpr SizeType maxSize() const noexcept {
            return std::numeric_limits<CharacterType>::max();
        }

        [[nodiscard]] constexpr bool empty() const noexcept {
            return (end_ - start_) <= 0;
        }

        // Modifiers
        // todo as required

        // Operations
        // todo as required

        // todo: constexpr auto startsWith()

        constexpr int compare(BaseStringView other) const noexcept {
            const SizeType minSize = std::min(length(), other.length());
            const auto compared = TraitsType::compare(data(), other.data(), minSize);
            if (compared != 0) {
                return compared;
            }

            if (length() == other.length()) {
                return 0;
            }

            if (length() < other.length()) {
                return -1;
            }

            return 1;
        }

        // Operators
        friend constexpr auto operator==(BaseStringView lhs, BaseStringView rhs) noexcept -> bool {
            return lhs.compare(rhs) == 0;
        }

    private:
        ConstIterator start_;
        ConstIterator end_;
    };

    using StringView = BaseStringView<char>;

    template<class Type>
    concept convertableToStringView = requires(Type* type) {
        std::BaseStringView<Type>(type);
    };
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_CPP_STRING_VIEW_H