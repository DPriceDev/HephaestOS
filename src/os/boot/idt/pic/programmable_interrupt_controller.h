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

#ifndef HEPHAIST_OS_KERNEL_BOOT_IDT_PROGRAMMABLE_INTERRUPT_CONTROLLER_H
#define HEPHAIST_OS_KERNEL_BOOT_IDT_PROGRAMMABLE_INTERRUPT_CONTROLLER_H

#include <cstdint>

namespace boot {
    constexpr uint8_t masterPicAddress = 0x20;// IO Address of Master PIC
    constexpr uint8_t slavePicAddress = 0xA0;// IO Address of Slave PIC
    constexpr uint8_t masterPicDataAddress = 0x21;// IO Data Address of Master PIC
    constexpr uint8_t slavePicDataAddress = 0xA1;// IO Data Address of Slave PIC


    constexpr uint8_t ICW1_ICW4 = 0x01; /* ICW4 (not) needed */
    constexpr uint8_t ICW1_SINGLE = 0x02; /* Single (cascade) mode */
    constexpr uint8_t ICW1_INTERVAL4 = 0x04; /* Call address interval 4 (8) */
    constexpr uint8_t ICW1_LEVEL = 0x08; /* Level triggered (edge) mode */
    constexpr uint8_t initializeCommand = 0x10;// Initialize the PIC

    constexpr uint8_t ICW4_8086 = 0x01; /* 8086/88 (MCS-80/85) mode */
    constexpr uint8_t ICW4_AUTO = 0x02; /* Auto (normal) EOI */
    constexpr uint8_t ICW4_BUF_SLAVE = 0x08; /* Buffered mode/slave */
    constexpr uint8_t ICW4_BUF_MASTER = 0x0C; /* Buffered mode/master */
    constexpr uint8_t ICW4_SFNM = 0x10; /* Special fully nested (not) */

    constexpr uint8_t picEoiFlag = 0x20;

    /**
     *
     * @param masterOffset
     * @param slaveOffset
     */
    void remapProgrammableInterruptController(uint8_t masterOffset, uint8_t slaveOffset);

    /**
     *
     * @param interruptCode
     */
    void sendEoiFlag(uint32_t interruptCode);
}// namespace boot

#endif// HEPHAIST_OS_KERNEL_BOOT_IDT_PROGRAMMABLE_INTERRUPT_CONTROLLER_H
