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

#include "../io/IO.hpp"
#include "../../memory/register_addr.hpp"

namespace SYS
{

namespace DISP{

    const int WIDTH(80);                                    //
    const int D_WIDTH(WIDTH*2);                             //
    const int HEIGHT(25);                                   //
    const int SCREEN_SIZE(WIDTH * HEIGHT);                  //

    const int DISPLAY_PAGES(8);                             //
    const int SCREEN_BUFFER_SIZE(DISPLAY_PAGES * WIDTH);    //
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
void MoveCursor(int x, int y)
{
	unsigned short pos = (y * DISP::WIDTH) + x;

	outportb(0x3D4, 0x0F);
	outportb(0x3D5, pos);
 
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, pos >> 8);
}

// Function: MoveCursor
// Desc: Moves the on screen text mode 0 cursor (bios screen) to a specified
//       Location.
// inputs: pos      - combined x and y position of cursor.
//
void MoveCursor(unsigned short pos)
{
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
unsigned int CursorPosition()
{
	outportb(0x3D4, 0x0F);
	unsigned int pos = inportb(0x3D5);
 
	outportb(0x3D4, 0x0E);
	pos += inportb(0x3D5) << 8;

    return pos;
}


//----------------------------------------------------------------------------//
// Function: ScrollScreen
// Desc: 
//       
//
void ScrollScreen()
{
    auto dest_ptr = (unsigned short*) VID_MEM_ADDR;
    auto source_ptr = (unsigned short*) (VID_MEM_ADDR + DISP::D_WIDTH);

    SYS::memcpy(dest_ptr, source_ptr, (DISP::SCREEN_SIZE-1)*2);
}

//----------------------------------------------------------------------------//
// Function: NewLine
// Desc: 
//       
//
void NewLine()
{
    int pos = (DISP::CursorPosition() / DISP::WIDTH) + 1;

    DISP::MoveCursor(pos * WIDTH);

    if(DISP::CursorPosition() >= DISP::SCREEN_SIZE){ 
        DISP::ScrollScreen();
        DISP::MoveCursor(DISP::WIDTH * (DISP::HEIGHT - 1));
    }
}

//----------------------------------------------------------------------------//
// Function: ClearScreen
// Desc: 
//       
//
void cls(int colour = 0x0F)
{
    auto dest_ptr = (volatile unsigned char*) VID_MEM_ADDR;

    for( int c = 0; c < DISP::SCREEN_SIZE*2; c += 2){
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
void PutStr(char* str, int fore_colour = 15, int back_colour = 15)
{
    // setup pointer to 0,0 location in the video memory.
    auto VideoMemory = (volatile unsigned char*) VID_MEM_ADDR;                       

    // while the is not empty.
    while( *str != 0 )
    {
        // if the x cursor is off the screen, reset to zero and add a row.
        if( *str == '\n' || *str == '\r' ){
            DISP::NewLine();
            *str++;
            continue;
        }

        // update cursor location in the video memory pointer.
        VideoMemory = (volatile unsigned char*) VID_MEM_ADDR 
                                                + DISP::CursorPosition()
                                                + DISP::CursorPosition();

        // add the string value and increment both memory and string.
        // add colour value and increment the memory to next cursor location.
        *VideoMemory++ = *str++;
        *VideoMemory++ = fore_colour;

        DISP::MoveCursor(DISP::CursorPosition() + 1);

        if(DISP::CursorPosition() >= DISP::SCREEN_SIZE){
            DISP::ScrollScreen();
            DISP::MoveCursor(DISP::WIDTH * (DISP::HEIGHT - 1));
        }
    }
}


} // End of SYS namespace
#endif