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
        void* data { nullptr };
        void (*onDereference) (void*) { nullptr };
        void (*onIncrement) (void*) { nullptr };
        void (*onAssignCharacter) (void*, char) { nullptr };

    public:
        using pointer = void;
        using reference = void;
        using valueType = void;
        using differenceType = std::ptrdiff_t;

        StandardOutputIterator() = default;

        StandardOutputIterator(
            void* data,
            void (*onDereference) (void*),
            void (*onAssignCharacter) (void*, char),
            void (*onIncrement) (void*)
        ) : data(data),
        onDereference(onDereference),
        onIncrement(onIncrement),
        onAssignCharacter(onAssignCharacter) { }

        StandardOutputIterator& operator=(char character) {
            onAssignCharacter(data, character);
            return *this;
        }

        StandardOutputIterator& operator*() {
            onDereference(data);
            return *this;
        }

        constexpr StandardOutputIterator& operator++() {
            onIncrement(data);
            return *this;
        }

        StandardOutputIterator& operator++(int) {
            onIncrement(data);
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
