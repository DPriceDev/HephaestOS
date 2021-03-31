////////////////////////////////////////////////////////////////////////////////
// Title:           Display System Functions
// Filename:        display.hpp
// Last Changed:    17/08/19
// Created:         17/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 07:46 18/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#ifndef SYS_DISPLAY_H
#define SYS_DISPLAY_H

#include "drivers/io/IO.hpp"
#include "kernel/memory/register_addr.hpp"

namespace SYS {

    namespace DISP {

        const unsigned int WIDTH(80);                                    //
        const unsigned int D_WIDTH(WIDTH * 2);                             //
        const unsigned int HEIGHT(25);                                   //
        const unsigned int SCREEN_SIZE(WIDTH * HEIGHT);                  //

        const unsigned int DISPLAY_PAGES(8);                             //
        const unsigned int SCREEN_BUFFER_SIZE(DISPLAY_PAGES * WIDTH);    //
        const unsigned char BLANK(0x20);


//----------------------------------------------------------------------------//
// CURSOR FUNCTIONS //

// Function: MoveCursor
// Desc: Moves the on screen text mode 0 cursor (bios screen) to a specified
//       Location.
//
// inputs: x        - x coordinate of the cursor.
//         y        - y coordinate of the cursor.
//
        void MoveCursor(unsigned int x, unsigned int y) {
            unsigned char position = static_cast<unsigned char>((y * DISP::WIDTH) + x);

            outportb(0x3D4, 0x0F);
            outportb(0x3D5, position);

            outportb(0x3D4, 0x0E);
            outportb(0x3D5, position >> 8);
        }

// Function: MoveCursor
// Desc: Moves the on screen text mode 0 cursor (bios screen) to a specified
//       Location.
// inputs: pos      - combined x and y position of cursor.
//
        void MoveCursor(unsigned char pos) {
            outportb(0x3D4, 0x0F);
            outportb(0x3D5, pos);

            outportb(0x3D4, 0x0E);
            outportb(0x3D5, pos >> 8);
        }

//------------------------------------------------//
// Function: CursorPosition
// Desc: functions gets the cursor position for text mode 0 (BIOs screen) from
//       the port registers and returns it as an int.
//       This returns the Linear Position, (screen width * y) + x
//
// Output: int - returns the position of the cursor (linear position)

//
        unsigned int CursorPosition() {
            outportb(0x3D4, 0x0F);
            unsigned int pos = inportb(0x3D5);

            outportb(0x3D4, 0x0E);
            pos += static_cast<unsigned int>(inportb(0x3D5) << 8);

            return pos;
        }


//----------------------------------------------------------------------------//
// Function: ScrollScreen
// Desc: 
//       
//
        void ScrollScreen() {
            auto dest_ptr = reinterpret_cast<unsigned short *>(VID_MEM_ADDR);
            auto source_ptr = reinterpret_cast<unsigned short *>(VID_MEM_ADDR + DISP::D_WIDTH);

            SYS::memcpy(dest_ptr, source_ptr, (DISP::SCREEN_SIZE - 1) * 2);
        }

//----------------------------------------------------------------------------//
// Function: NewLine
// Desc: 
//       
//
        void NewLine() {
            unsigned int position = (DISP::CursorPosition() / DISP::WIDTH) + 1;

            DISP::MoveCursor(static_cast<unsigned char>(position * WIDTH));

            if (DISP::CursorPosition() >= DISP::SCREEN_SIZE) {
                DISP::ScrollScreen();
                DISP::MoveCursor(static_cast<unsigned char>(DISP::WIDTH * (DISP::HEIGHT - 1)));
            }
        }

//----------------------------------------------------------------------------//
// Function: ClearScreen
// Desc: 
//       
//
        void cls(unsigned char colour = 0x0F) {
            auto dest_ptr = reinterpret_cast<unsigned char *>(VID_MEM_ADDR);

            for (unsigned int c = 0; c < DISP::SCREEN_SIZE * 2; c += 2) {
                *dest_ptr++ = BLANK;
                *dest_ptr++ = colour;
            }

            DISP::MoveCursor(0);
        }

    }   // End of DISP namespace

//----------------------------------------------------------------------------//
// Function: PutStr
// Desc: While in text mode, this function will write to the screen the 
//       provided string (char array), in the provided foreground and,
//       background colour, at the cursor location.
//
// inputs: str      - char array holding string to output to screen.
//         colour   - int holding colour value.
//
    void PutStr(const char *str, char fore_colour = 15 /*, int back_colour = 15 */) {
        // setup pointer to 0,0 location in the video memory.
        auto VideoMemory = reinterpret_cast<unsigned char *>(VID_MEM_ADDR);

        // while the is not empty.
        while (*str != 0) {
            // if the x cursor is off the screen, reset to zero and add a row.
            if (*str == '\n' || *str == '\r') {
                DISP::NewLine();
                str++;
                continue;
            }

            // update cursor location in the video memory pointer.
            VideoMemory = reinterpret_cast<unsigned char *>(VID_MEM_ADDR
                                                            + DISP::CursorPosition()
                                                            + DISP::CursorPosition());

            // add the string value and increment both memory and string.
            // add colour value and increment the memory to next cursor location.
            *VideoMemory++ = static_cast<unsigned char>(*str++);
            *VideoMemory++ = static_cast<unsigned char>(fore_colour);

            DISP::MoveCursor(static_cast<unsigned char>(DISP::CursorPosition() + 1));

            if (DISP::CursorPosition() >= DISP::SCREEN_SIZE) {
                DISP::ScrollScreen();
                DISP::MoveCursor(static_cast<unsigned char>(DISP::WIDTH * (DISP::HEIGHT - 1)));
            }
        }
    }


} // End of SYS namespace
#endif