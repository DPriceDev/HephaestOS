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

#ifndef HEPHAIST_OS_KERNEL_LIBRARY_ARRAY_H
#define HEPHAIST_OS_KERNEL_LIBRARY_ARRAY_H

#include <stdint.h>

namespace kernel {

    template<typename Type, uint32_t length>
    struct Array {
        Type array[length];

        Type& at(uint32_t index) { return array[index]; }
        const Type& at(uint32_t index) const { return array[index]; }

        [[nodiscard]] uint32_t size() const noexcept { return length; }

        Type& operator[](uint32_t index) { return array[index]; }
        const Type& operator[](uint32_t index) const { return array[index]; }

        Type* data() noexcept { return array; }
        const Type* data() const noexcept { return array; }
    };
}
#endif //HEPHAIST_OS_KERNEL_LIBRARY_ARRAY_H
