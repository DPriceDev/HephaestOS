/* Copyright (C) 2023 David Price - All Rights Reserved
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

#include "global_descriptor.h"
#include <stdoffset.h>

namespace boot {

    /**
     * Constructs a Global descriptor that can be inserted in a Global descriptor table. This takes a set of
     * addresses, sizes, flags and settings to define a Global Descriptor. The x86 implementation of the
     * Global Descriptor splits the base address and limit across the structure; therefore the lower, mid, and
     * upper sections of the baseAddress and memoryLimit are bit-masked and bit-shifted into place.
     *
     * @param baseAddress is the memory address that this segment will begin at.
     * @param memoryLimit is the size of the segment in bytes.
     * @param access describe the type of segment, privilege and other parameters.
     * @param flags describe the size (16 or 32 bit) and granularity (bit or page) of the segment memory.
     * @return Global Descriptor constructed from the parameters.
     */
    auto constructGlobalDescriptor(
        const uintptr_t baseAddress,
        const uint32_t memoryLimit,
        const Access& access,
        const Flags& flags
    ) -> GlobalDescriptor {
        return GlobalDescriptor { .lowerLimit = static_cast<uint16_t>((memoryLimit & std::Mask16Bit)),
                                  .lowerBase = static_cast<uint16_t>((baseAddress & std::Mask16Bit)),
                                  .midBase = static_cast<uint8_t>((baseAddress >> std::Offset16Bit) & std::Mask8Bit),
                                  .access = access,
                                  .upperLimit = static_cast<uint8_t>((memoryLimit >> std::Offset16Bit) & std::Mask4Bit),
                                  .available = flags.available,
                                  .longMode = flags.longMode,
                                  .size = flags.size,
                                  .granularity = flags.granularity,
                                  .upperBase =
                                      static_cast<uint8_t>((baseAddress >> std::Offset24Bit) & std::Mask8Bit) };
    }
}// namespace boot