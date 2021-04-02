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

#ifndef HEPHAISTOS_MULTIBOOT_INFO_H
#define HEPHAISTOS_MULTIBOOT_INFO_H

#include "kernel/types.h"

namespace kernel {

    struct MultiBootInfo {
        uint32_t flags;
        uint32_t lowerMemorySize;
        uint32_t upperMemorySize;
        uint32_t bootDevice;
        uint32_t commandLine;
        uint32_t moduleCount;
        uint32_t moduleAddress;                     // Can be a pointer to a struct
        uint32_t symbolTableLocation[4];            // Can be a struct
        uint32_t memoryMapLength;
        uint32_t memoryMapAddress;
        uint32_t drivesLength;
        uint32_t drivesAddress;                     // Can be a pointer to a struct
        uint32_t configTable;
        uint32_t advancedPowerManagementTable;
        uint32_t vbeControlInfo;
        uint32_t vbeModeInfo;
        uint32_t vbeMode;
        uint32_t vbeInterfaceSeg;
        uint32_t vbeInterfaceOff;
        uint32_t vbeInterfaceLength;
    } __attribute__((aligned(128)));

}
#endif //HEPHAISTOS_MULTIBOOT_INFO_H
