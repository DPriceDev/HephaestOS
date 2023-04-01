// Copyright (C) 2023 David Price - All Rights Reserved
// This file is part of HephaestOS.
//
// HephaestOS is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// HephaestOS is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
//

#ifndef HEPHAEST_OS_INIT_H
#define HEPHAEST_OS_INIT_H

#include "grub/multiboot_info.h"
#include <boot_info.h>
#include <memory/boot_allocator.h>

namespace boot {
    extern "C" void loadKernelSegment();

    extern "C" void enableInterrupts();

    extern "C" void init(MultiBootInfo& info, uint32_t magic, uint32_t stackPointer, BootInfo bootInfo);

    void initializeSerialPort();

    void initializeDescriptorTables(uint32_t stackPointer);

    void setupInterrupts();

    auto findNextAvailableMemory(const std::Span<ModuleEntry>& bootModules, const BootInfo& bootInfo) -> uintptr_t;

    void enterKernelModule(
        uintptr_t stackPointer,
        uintptr_t kernelAddress,
        const MultiBootInfo& multiBootInfo,
        const BootInfo& bootInfo,
        BootAllocator& allocator
    );
}// namespace boot

#endif// HEPHAEST_OS_INIT_H
