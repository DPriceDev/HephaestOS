//
// Created by david on 12/12/2021.
//

#include <kernel/lib/libc/stdint.h>
#include "global_descriptor.h"

namespace kernel::boot::gdt {

    //
    constexpr uint16_t Mask16Bit = 0xFFFF;
    constexpr uint8_t Mask8Bit = 0xFF;
    constexpr uint8_t Mask4Bit = 0xF;

    //
    constexpr uint8_t Offset16Bit = 16U;
    constexpr uint8_t Offset24Bit = 24U;

    /**
     *
     * @param baseAddress
     * @param memoryLimit
     * @param access
     * @param flags
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