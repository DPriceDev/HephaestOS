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

#ifndef HEPHAIST_OS_KERNEL_LIB_STD_INT_H
#define HEPHAIST_OS_KERNEL_LIB_STD_INT_H

#include <cstdint>

// todo: add as library do not copy
namespace kernel {

    // todo: move to common file
    // Set of bit-masks that can be used to mask parts of an Integer.
    constexpr uint32_t Mask30Bit = 0x40000000;
    constexpr uint32_t Mask20Bit = 0xFFFFF;
    constexpr uint16_t Mask16Bit = 0xFFFF;
    constexpr uint16_t Mask12Bit = 0xFFF;
    constexpr uint16_t Mask10Bit = 0x3FF;
    constexpr uint8_t Mask8Bit = 0xFF;
    constexpr uint8_t Mask4Bit = 0xF;

    // todo: move to common file
    // Set of bit-offsets that can be used to move an integer by a power of 2.
    constexpr uint8_t Offset12Bit = 12U;
    constexpr uint8_t Offset16Bit = 16U;
    constexpr uint8_t Offset22Bit = 22U;
    constexpr uint8_t Offset24Bit = 24U;
    constexpr uint8_t Offset32Bit = 32U;
}

#endif // HEPHAIST_OS_KERNEL_LIB_STD_INT_H
