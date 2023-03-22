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

#ifndef HEPHAIST_OS_KERNEL_LIBRARY_CPP_FORMAT_H
#define HEPHAIST_OS_KERNEL_LIBRARY_CPP_FORMAT_H

#include <format_base.h>
#include <iterator.h>

namespace std {

    class StandardOutputIterator {
        const void* data_ { nullptr };
        void (*onDereference_) (const void*) { nullptr };
        void (*onIncrement_) (const void*) { nullptr };
        void (*onAssignCharacter_) (const void*, char) { nullptr };

    public:
        using pointer = void;
        using reference = void;
        using valueType = void;
        using differenceType = std::ptrdiff_t;

        StandardOutputIterator() = default;

        explicit StandardOutputIterator(
            const void* output,
            void (*onDereference) (const void*) = [] (const void*) { /* no-op */ },
            void (*onAssignCharacter) (const void*, char) = [] (const void*, char) { /* no-op */ },
            void (*onIncrement) (const void*) = [] (const void*) { /* no-op */ }
        ) : data_(output),
        onDereference_(onDereference),
        onIncrement_(onIncrement),
        onAssignCharacter_(onAssignCharacter) { }

        StandardOutputIterator& operator=(char character) {
            onAssignCharacter_(data_, character);
            return *this;
        }

        StandardOutputIterator& operator*() {
            onDereference_(data_);
            return *this;
        }

        constexpr StandardOutputIterator& operator++() {
            onIncrement_(data_);
            return *this;
        }

        StandardOutputIterator& operator++(int) {
            onIncrement_(data_);
            return *this;
        }
    };

    class KernelFormatOutput {
        StandardOutputIterator iterator;

    public:
        static auto getInstance() -> KernelFormatOutput&;

        // Set the output iterator for logging
        void setStandardOutputIterator(StandardOutputIterator outputIterator) {
            iterator = outputIterator;
        }

        // Accessor
        [[nodiscard]]
        auto out() -> StandardOutputIterator& {
            return iterator;
        }
    };

    template<class... Args>
    void print(
        std::convertableToStringView auto* format,
        Args... args
    ) {
        auto instance = KernelFormatOutput::getInstance();
        auto output = instance.out();
        std::formatTo(output, format, args...);
    }
}

#endif // HEPHAIST_OS_KERNEL_LIBRARY_CPP_FORMAT_H
