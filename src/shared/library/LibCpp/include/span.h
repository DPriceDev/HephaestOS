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

#ifndef HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_SPAN_H
#define HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_SPAN_H

#include <concepts>
#include <limits>
#include "iterator.h"

namespace std {

    /**
     * Dynamic Extent defines both the maximum size of a span, as well as signalling that
     * the span has a size defined dynamically instead of statically, such as with an array.
     */
    inline constexpr std::size_t dynamicExtent = std::numeric_limits<std::size_t>::max();

    namespace detail {

        /**
         * Span Storage defines a statically defined struct containing a pointer to the
         * start of a contiguous length of data of type @tparam Type with a size of
         * @tparam Size.
         */
        template<class Type, std::size_t Size>
        struct SpanStorage {
            Type* data = nullptr;
            static constexpr std::size_t size = Size;

            constexpr SpanStorage() noexcept = default;

            constexpr SpanStorage(Type* data) noexcept
                : data(data) { }
        };

        /**
         * Span Storage specializes SpanStorage and alters it to store a pointer to the
         * start of a contiguous length of data of type @tparam Type with a dynamically
         * defined size.
         */
        template<class Type>
        struct SpanStorage<Type, dynamicExtent> {
            Type* data = nullptr;
            std::size_t size = 0;

            constexpr SpanStorage() noexcept = default;

            constexpr SpanStorage(Type* data, std::size_t size) noexcept
                : data(data), size(size) { }
        };
    }

    /**
     * Span defines a container that does not own the data it contains. It usually takes
     * a pointer to data of type @tparam Type with either a statically or dynamically set
     * size defined in the @tparam Extent parameter; if the @tparam Extent is dynamicExtent,
     * then it has dynamic storage, if it is defined as some size_t, then it is static.
     */
    template<class Type, std::size_t Extent = std::dynamicExtent>
    class Span {
        detail::SpanStorage<Type, Extent> storage;

    public:
        // Container Definitions
        using elementType = Type;
        using valueType = std::remove_cv_t<elementType>;
        using sizeType = std::size_t;
        using differenceType = std::ptrdiff_t;
        using pointer = elementType*;
        using constPointer = const elementType*;
        using reference = elementType&;
        using constReference = const elementType&;
        using iterator = pointer;
        using reverseIterator = std::reverseIterator<iterator>;

        // Span Definitions
        static constexpr std::size_t extent = Extent;

        // Constructors

        /**
         * Constructs an empty span with null data and a size of 0.
         */
        explicit(extent == 0 || extent == std::dynamicExtent)
        constexpr Span() noexcept: storage(nullptr, 0) { }

        /**
         * Constructs a dynamic span starting at @param first with a size of @param size.
         */
        explicit(extent != std::dynamicExtent)
        constexpr Span(pointer first, sizeType size) : storage(first, size) { }

        /**
         * Constructs a dynamic span from two pointers, with the size of the span being the
         * difference between the pointers.
         */
        explicit(extent != std::dynamicExtent)
        constexpr Span(pointer first, pointer last) : storage(first, static_cast<sizeType>(last - first)) { }

        /**
         * Constructs a static span from an @param array parameter with a statically
         * defined @tparam Size.
         */
        template<std::size_t Size>
        constexpr Span(elementType (& array)[Size]) noexcept : storage(array, Size) { }

        // todo: Add after implementing std::array
//        template<class U, std::size_t N>
//        constexpr Span(std::array<U, N>& arr ) noexcept {
//            /* todo */
//        }

        // todo: Add after implementing std::array
//        template< class U, std::size_t N >
//        constexpr span( const std::array<U, N>& arr ) noexcept {
//            /* todo */
//        }

        // todo: Add after implementing ranges?
//        template< class R >
//        explicit(extent != std::dynamic_extent)
//        constexpr span( R&& range );

//      todo: const from other span?
//        template<std::size_t Size>
//        explicit(extent != std::dynamicExtent && Size == std::dynamicExtent)
//        constexpr Span(const std::Span<Type, Size>& source) noexcept {
//            /* todo */
//        }

        constexpr Span(const Span& other) noexcept = default;

        // Member Functions

        // Assignment
        constexpr Span& operator=(const Span& other) noexcept = default;

        // Iterators
        auto begin() const -> iterator {
            return data();
        }

        auto end() const -> iterator {
            return data() + size();
        }

        auto rbegin() -> reverseIterator {
            return reverseIterator(data() + size());
        }

        auto rend() -> reverseIterator {
            reverseIterator(storage.data);
        }

        // Element Access
        auto front() -> reference {
            return *data();
        }

        auto back() -> reference {
            return *(data() + size());
        }

        constexpr auto operator[](sizeType index) const -> reference {
            return *(data() + index);
        }

        constexpr auto data() const noexcept -> pointer {
            return storage.data;
        }

        // Observers
        [[nodiscard]] constexpr auto size() const noexcept -> sizeType {
            return storage.size;
        }

        [[nodiscard]] constexpr auto sizeInBytes() const noexcept -> sizeType {
            return size() * sizeof(elementType);
        }

        [[nodiscard]] constexpr auto empty() const noexcept -> bool {
            return size() == 0;
        }

        // todo: Subviews

    };
}

#endif // HEPHAIST_OS_SHARED_LIBRARY_LIB_CPP_SPAN_H