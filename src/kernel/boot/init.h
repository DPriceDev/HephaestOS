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

#ifndef HEPHAISTOS_INIT_H
#define HEPHAISTOS_INIT_H

#include <boot_info.h>
#include "grub/multiboot_info.h"


namespace kernel::boot {

    extern "C" void loadKernelSegment();

    extern "C" void enableInterrupts();

    extern "C" void init(
        kernel::boot::MultiBootInfo * info,
        uint32_t magic,
        uint32_t stackPointer,
        kernel::boot::BootInfo bootInfo
    );

    void initializeSerialPort();

    void initializeDescriptorTables(uint32_t stackPointer);

    void setupInterrupts();

    auto findNextAvailableMemory(const std::Span<ModuleEntry>& bootModules, const BootInfo& bootInfo) -> uintptr_t;

    void enterKernelModule(uintptr_t kernelAddress);
}

#endif //HEPHAISTOS_INIT_H
