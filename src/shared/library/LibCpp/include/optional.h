// Copyright (C) 2023 David Price - All Rights Reserved
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

#ifndef HEPHAISTOS_OPTIONAL_H
#define HEPHAISTOS_OPTIONAL_H

#include "bits/move.h"

namespace std {

    struct NullOptional {};

    inline constexpr NullOptional nullOption {};

    template<class Type>
    class Optional {
        union {
            NullOptional nullValue_;
            Type value_;
        };
        bool hasResult;

    public:
        // Constructors
        constexpr Optional() noexcept : nullValue_(nullOption), hasResult(false) { }
        explicit(false) constexpr Optional(std::NullOptional nullValue) noexcept : nullValue_(nullValue), hasResult(false) { }

        template <class U = Type>
        explicit constexpr Optional(U&& value) : value_(std::forward<U>(value)), hasResult(true) { }

        // Destructor
        constexpr ~Optional() {
            value().Type::~Type();
        }

        // Operators
        constexpr const Type* operator->() const noexcept { return &value_; }

        constexpr Type* operator->() noexcept { return &value_; }

        constexpr const Type& operator*() const& noexcept { return &value_; }

        constexpr Type& operator*() & noexcept { return value_; }

        constexpr const Type&& operator*() const&& noexcept { return value_; }

        constexpr Type&& operator*() && noexcept { return value_; }

        constexpr explicit operator bool() const noexcept { return hasResult; }

        // Accessors
        constexpr Type& value() & { return value_; }

        constexpr const Type& value() const & { return value_; }

        constexpr Type&& value() && { return value_; }

        constexpr const Type&& value() const && { return value_; }

        template<class U>
        constexpr Type valueOr(U&& defaultValue) const& {
            if (!hasResult) {
                return std::forward<U>(defaultValue);
            }
            return value_;
        }

        template<class U>
        constexpr Type valueOr(U&& defaultValue) && {
            if (!hasResult) {
                return std::forward<U>(defaultValue);
            }
            return value_;
        }

        // Validators
        [[nodiscard]] constexpr bool hasValue() const noexcept { return hasResult; }
    };
}

#endif //HEPHAISTOS_OPTIONAL_H
