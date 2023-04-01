/* Copyright (C) 2021 David Price - All Rights Reserved
 * This file is part of HephaestOS.
 *
 * HephaestOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HephaestOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HephaestOS.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef HEPHAEST_OS_KERNEL_BOOT_MULTIBOOT_INFO_H
#define HEPHAEST_OS_KERNEL_BOOT_MULTIBOOT_INFO_H

#include <stdoffset.h>

namespace boot {

    static constexpr uint8_t MULTIBOOT_MEMORY_AVAILABLE = 1;

    static constexpr uint8_t MULTIBOOT_MEMORY_RESERVED = 2;

    static constexpr uint8_t MULTIBOOT_MEMORY_ACPI_RECLAIMABLE = 3;

    static constexpr uint8_t MULTIBOOT_MEMORY_NVS = 4;

    static constexpr uint8_t MULTIBOOT_MEMORY_BAD_RAM = 5;

    struct [[gnu::packed]] MultiBootFlags {
        bool isPageAligned : 1;
        bool isMemoryAvailable : 1;
        bool isVideoModeAvailable : 1;
        bool unusedFlagA : 1;
        bool unusedFlagB : 1;
        bool unusedFlagC : 1;
        bool isMemoryMapAvailable : 1;
        uint32_t unusedLowerFlags : 9;
        bool hasExecutableHeader : 1;
        uint32_t unusedUpperFlags : 15;
    };

    struct [[gnu::packed]] BootDevice {
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
    };

    struct [[gnu::packed]] ElfSectionTable {
        uint32_t count;
        uint32_t size;
        uint32_t tableAddress;
        uint32_t shndx;
    };

    struct [[gnu::packed]] ModuleEntry {
        uint32_t moduleStart;
        uint32_t moduleEnd;
        uint32_t string;
        uint32_t unused;
    };

    struct [[gnu::packed]] MemoryMapEntry {
        uint32_t size;
        uint32_t addr_low;
        uint32_t addr_high;
        uint32_t len_low;
        uint32_t len_high;
        uint32_t type;
    };

    /**
     * todo: Comment
     */
    struct [[gnu::packed]] MultiBootInfo {
        MultiBootFlags flags;
        uint32_t lowerMemorySize;
        uint32_t upperMemorySize;
        BootDevice bootDevice;
        uint32_t commandLine;
        uint32_t moduleCount;
        ModuleEntry* modulePtr;
        ElfSectionTable symbolTableLocation;
        uint32_t memoryMapLength;
        MemoryMapEntry* memoryMapPtr;
        uint32_t drivesLength;
        uint32_t drivesAddress;// Can be a pointer to a struct
        uint32_t configTable;
        uint32_t advancedPowerManagementTable;
        uint32_t vbeControlInfo;
        uint32_t vbeModeInfo;
        uint32_t vbeMode;
        uint32_t vbeInterfaceSeg;
        uint32_t vbeInterfaceOff;
        uint32_t vbeInterfaceLength;
    };
}// namespace boot
#endif// HEPHAEST_OS_KERNEL_BOOT_MULTIBOOT_INFO_H
