//
// Created by david on 12/12/2021.
//

#include <kernel/lib/libc/stdint.h>
#include "global_descriptor.h"

namespace kernel::boot::gdt {

    // todo: move to common file
    // Set of bit-masks that can be used to mask parts of an Integer.
    constexpr uint16_t Mask16Bit = 0xFFFF;
    constexpr uint8_t Mask8Bit = 0xFF;
    constexpr uint8_t Mask4Bit = 0xF;

    // todo: move to common file
    // Set of bit-offsets that can be used to move an integer by a power of 2.
    constexpr uint8_t Offset16Bit = 16U;
    constexpr uint8_t Offset24Bit = 24U;

    /**
     * Constructs a Global descriptor that can be used
     * @param baseAddress is the memory address that this segment will begin at.
     * @param memoryLimit is the size of the segment in bytes.
     * @param access describe the type of segment, privilege and other parameters.
     * @param flags describe the size (16 or 32 bit) and granularity (bit or page) of the segment memory.
     * @return
     */
    GlobalDescriptor constructGlobalDescriptor(
            const uint32_t baseAddress,
            const uint32_t memoryLimit,
            const Access &access,
            const Flags &flags
    ) {
        return GlobalDescriptor{
                .lowerLimit     = static_cast<uint16_t>((memoryLimit & Mask16Bit)),
                .lowerBase      = static_cast<uint16_t>((baseAddress & Mask16Bit)),
                .midBase        = static_cast<uint8_t>((baseAddress >> Offset16Bit) & Mask8Bit),
                .access         = access,
                .upperLimit     = static_cast<uint8_t>((memoryLimit >> Offset16Bit) & Mask4Bit),
                .available      = flags.available,
                .longMode       = flags.longMode,
                .size           = flags.size,
                .granularity    = flags.granularity,
                .upperBase      = static_cast<uint8_t>((baseAddress >> Offset24Bit) & Mask8Bit)
        };
    }
}