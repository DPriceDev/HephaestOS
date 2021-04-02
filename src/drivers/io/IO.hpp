////////////////////////////////////////////////////////////////////////////////
// Title:           IO Calls and Functions
// Filename:        IO.hpp, IO.cpp
// Last Changed:    17/08/19
// Created:         17/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 01:32 17/08/19: printf changed to PutStr and PutChar added.
//      - 00:32 17/08/19: printf added.
//      - 00:32 17/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#ifndef HEPHAIST_OS_DRIVERS_IO_IO_H
#define HEPHAIST_OS_DRIVERS_IO_IO_H

#include "kernel/types.h"
#include "kernel/memory/register_addr.hpp"


namespace kernel {

    ////////////////////////////////////////////////////////////////////////////////
    // Function: WriteAdrInt
    // Desc: function to write a word (int32) to a memory location.
    //
    // inputs: addr - address of the memory location to write to.
    //         data - short int to write to location.
    //
    inline void WriteAdrInt(kernel::int32_t addr, short data)
    {
        auto addr_ptr = &addr;
        *addr_ptr = data;
    }


    // Function: WriteAdrbyte
    // Desc: function to write a byte (char) to a memory location.
    //
    // inputs: port - address of the memonry location to write to.
    //         data - char to write to location
    //
    inline void WriteAdrbyte(int addr, char data)
    {
        auto addr_ptr = &addr;
        *addr_ptr = data;
    }


    //----------------------------------------------------------------------------//
    // Function: inportb
    // Desc: (Aqquired Function) Retreives the value at the specified port
    //       location.
    //
    // input: port - port location.
    //
    // Output: char - value of the port.
    //
    inline unsigned char inportb(unsigned int port)
    {
       unsigned char ret;
       asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
       return ret;
    }


    // Function: outportb
    // Desc:(Aqquired Function) Puts a char value into a specified port location.
    //
    // inputs: port  - location of the port.
    //         value - char sized value to place into port.
    //
    inline void outportb(unsigned int port, unsigned char value)
    {
       asm volatile ("outb %%al,%%dx": :"d" (port), "a" (value));
    }

//    //----------------------------------------------------------------------------//
//    // Function: memcpy
//    // Desc: (Aqquired Function) Copys a set of memory from one location to another.
//    //
//    // input: *destination -
//    //        *source      -
//    //        num          -
//    //
//    void memcpy( void *destination, void *source, unsigned long long num ){
//
//       char *cStr = static_cast<char*>(source);
//       char *cDestination = static_cast<char*>(destination);
//
//       for (unsigned long long i = 0; i < num; i++)
//           cDestination[i] = cStr[i];
//
//    }
//
//    //----------------------------------------------------------------------------//
//    // Function: memset
//    // Desc: (Aqquired Function) sets a block of memory to a specified value/
//    //
//    // input: *destination -
//    //        *value      -
//    //          num          -
//    //
//    void memset( void *destination, int value, unsigned long long num ){
//
//       int *cDestination = static_cast<int*>(destination);
//
//       for (unsigned long long i = 0; i < num; i++)
//           cDestination[i] = value;
//
//    }

}

#endif
////////////////////////////////////////////////////////////////////////////////