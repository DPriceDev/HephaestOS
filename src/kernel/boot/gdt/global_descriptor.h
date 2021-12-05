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
#ifndef HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H
#define HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H

namespace kernel::boot::gdt {

    struct Access {
        bool accessed: 1;
        bool readWritable: 1;
        bool isConforming: 1;
        bool isExecutable: 1;
        bool descriptorType: 1;
        uint8_t privilege: 2;
        bool present: 1;
    } __attribute__((packed));

    struct Flags {
        bool available: 1;
        bool longMode: 1;
        bool size: 1;
        bool granularity: 1;
    } __attribute__((packed));

    struct GlobalDescriptor {
        uint16_t lowerLimit;
        uint32_t lowerBase: 16;
        uint32_t midBase: 8;
        bool accessed: 1;
        bool readWritable: 1;
        bool isConforming: 1;
        bool isExecutable: 1;
        bool descriptorType: 1;
        uint8_t privilege: 2;
        bool present: 1;
        uint8_t upperLimit: 4;
        bool available: 1;
        bool longMode: 1;
        bool size: 1;
        bool granularity: 1;
        uint8_t upperBase;
    } __attribute__((packed));

    constexpr Access zeroAccess         {false, false, false, false, false, 0, false};
    constexpr Access codeKernelAccess   {false, true, false, true, true, 0, true};
    constexpr Access dataKernelAccess   {false, true, false, false, true, 0, true};
    constexpr Access codeUserAccess     {false, true, false, true, true, 3, true};
    constexpr Access dataUserAccess     {false, true, false, false, true, 3, true};

    constexpr Access tssEntryAccess     {true, false, false, true, false, 0, true};

    constexpr Flags zeroFlags   {false, false, false, false};
    constexpr Flags gran32Flags {true, false, true, true};
    constexpr Flags tssFlags   {false, false, false, false};
}

#endif // HEPHAIST_OS_KERNEL_BOOT_GDT_GLOBAL_DESCRIPTOR_H