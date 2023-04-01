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

#ifndef HEPHAEST_OS_SHARED_LIBRARY_CPP_FUNCTIONAL_REFERENCE_WRAPPER_H
#define HEPHAEST_OS_SHARED_LIBRARY_CPP_FUNCTIONAL_REFERENCE_WRAPPER_H

#include <bits/move.h>

namespace std {


    namespace detail {
        // todo: What is this doing? casting T to U? can i use a concept?
        template <class T> constexpr T& FUN(T& t) noexcept { return t; }
        template <class T> void FUN(T&&) = delete;
    }

    template <class Type>
    class ReferenceWrapper {
      public:
        using type = Type;

        // Constructors
        template<class U>
        constexpr ReferenceWrapper(U&& reference) /* todo: noexcept(...) */ : value(std::addressof(detail::FUN<Type>(std::forward<U>(reference)))) { }

        constexpr operator Type& () const noexcept {
            return *value;
        }

        constexpr Type& get() const noexcept {
            return *value;
        }

      private:
        Type* value;
    };
}

#endif// HEPHAEST_OS_SHARED_LIBRARY_CPP_FUNCTIONAL_REFERENCE_WRAPPER_H
