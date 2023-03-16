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

#ifndef HEPHAISTOS_BOOTALLOCATOR_H
#define HEPHAISTOS_BOOTALLOCATOR_H

#include <cstdint>

namespace kernel::boot {

    class BootAllocator {
        std::uintptr_t memoryPointer;
        std::uintptr_t virtualPointer;

    public:
        static BootAllocator& getInstance() {
            static BootAllocator instance;
            return instance;
        }

        void setMemoryPointer(std::uintptr_t pointer, std::uintptr_t virtualPointer) {
            this->memoryPointer = pointer;
            this->virtualPointer = virtualPointer;
        }

        auto allocateMemory(std::size_t count) -> void* {
            auto pointer = memoryPointer;
            memoryPointer += count;
            return reinterpret_cast<void*>(pointer);
        }
    };
}

#endif //HEPHAISTOS_BOOTALLOCATOR_H
