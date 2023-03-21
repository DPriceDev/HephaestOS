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

#ifndef HEPHAIST_OS_KERNEL_LIB_DEBUG_H
#define HEPHAIST_OS_KERNEL_LIB_DEBUG_H

namespace debug {

    /**
     * Magic Break Point will stop execution within bochs and switch to the
     * internal debugger.
     */
    extern "C" void magicBreakPoint();
}

#endif // HEPHAIST_OS_KERNEL_LIB_DEBUG_H
