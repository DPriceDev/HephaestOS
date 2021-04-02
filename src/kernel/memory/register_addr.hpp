////////////////////////////////////////////////////////////////////////////////
// Title:           Register Addresses
// Filename:        register_Addr.hpp
// Last Changed:    18/08/19
// Created:         18/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 09:01 18/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#ifndef SYS_REG_ADDR_H
#define SYS_REG_ADDR_H

#include "kernel/types.h"

namespace address {
    constexpr kernel::uint32_t videoMemoryAddress = 0xb8000;
    constexpr kernel::uint32_t videoCursorHighAddress = 0x3D5;
    constexpr kernel::uint32_t videoCursorLowAddress = 0x3D4;
}

#endif