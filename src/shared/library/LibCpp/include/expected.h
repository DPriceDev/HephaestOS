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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_RESULT_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_RESULT_H

#include "bits/move.h"
#include <cstddef>

namespace std {

    template<class Error>
    class Unexpected {
        Error error_;

      public:
        explicit Unexpected(Error error) : error_(error) {}

        auto error() -> Error& { return error_; }
    };

    template<class Type, class Error>
    class Expected {
        union {
            Type value_;
            Error error_;
        };
        bool hasResult;

      public:
        // Constructors
        explicit Expected(Type result) : value_(result), hasResult { true } {}

        explicit(false) Expected(Unexpected<Error> error) : error_(error.error()), hasResult { false } {}

        // Operators
        constexpr const Type* operator->() const noexcept { return &value_; }

        constexpr Type* operator->() noexcept { return &value_; }

        constexpr const Type& operator*() const& noexcept { return &value_; }

        constexpr Type& operator*() & noexcept { return &value_; }

        constexpr const Type&& operator*() const&& noexcept { return &value_; }

        constexpr Type&& operator*() && noexcept { return &value_; }

        constexpr explicit operator bool() const noexcept { return hasResult; }

        // Accessors
        [[nodiscard]] constexpr auto& value() const noexcept { return value_; }

        [[nodiscard]] constexpr auto error() const noexcept { return error_; }

        template<class Default>
        auto valueOr(Default&& defaultValue) -> Type& {
            if (!hasValue()) {
                return std::forward(defaultValue);
            }
            return value();
        }

        // Validators
        [[nodiscard]] constexpr bool hasValue() const noexcept { return hasResult; }
    };
}// namespace std

#endif// HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_RESULT_H
