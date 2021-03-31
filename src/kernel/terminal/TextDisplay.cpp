#include "TextDisplay.hpp"

#include "../../libraries/string.hpp"
#include "../sys.hpp"


////////////////////////////////////////////////////////////////////////////////
// Function: TextDisplay CONSTRUCTOR
// desc: Constructor for the TextDisplay Class, used to initialise default
//       values.
//
// inputs:
//       _cursor_x  - initalised to top left corner (0)
//       _cursor_y  - initalised to top left corner (0)
//       _colour    - initalised to the colour white (15)  
//
TextDisplay::TextDisplay(): _cursor_x(0), _cursor_y(0), _colour(15)
{
}

// Function: TextDisplay DESTRUCTOR
// desc: called on deletion of object.
//
TextDisplay::~TextDisplay()
{
}


////////////////////////////////////////////////////////////////////////////////
// Function: Print
// desc: This function will print a string (char array) to the screen at the
//       cursors current location.
//       It will perform word wrapping for each row, and scrolling when printing
//       across the bottom of the screen.
//
// inputs:
//       str    - char array to be printed to the screen.
//       colour - colour, if chosen, to be printed in.
//
void TextDisplay::Print(char* str, int colour)
{
    if(colour >= 0 && colour <= 15){
        SYS::PutStr(str, colour);
    } else {
        SYS::PutStr(str, _colour);
    }

    UpdateCursorFromConsole();
}



//----------------------------------------------------------------------------//
// Function: SetColour
// desc: This function will set the colour of the next printed text.
//
// inputs:
//       colour - colour to be changed to. (0 - 15)
//
void TextDisplay::SetColour(int colour)
{
    if(colour >= 0 && colour <= 15){
        _colour = colour;
    }
}



//----------------------------------------------------------------------------//
// Function: SetCursor
// desc: This function will set location of the cursor on the screen. it will 
//       scale to the column position and scroll to the row position.
//
// inputs:
//       x - Location of the cursor in x (0 - 80)
//       y - Location of the cursor in y (0 - 25+)
//
void TextDisplay::SetCursor(int x, int y)
{
    if(x >= 0 && x <= SYS::DISP::WIDTH
        && x >= 0 && x <= SYS::DISP::SCREEN_BUFFER_SIZE)
    {
        _cursor_x = x;
        _cursor_y = y;

        SYS::DISP::MoveCursor(x,y);
    }
    else return;
}



//----------------------------------------------------------------------------//
// Function: AdvanceCursor
// desc: This function will move the cursor location forward by the desired 
//       amount. it will wrap to the next line if too long, and scroll the
//       screen down if past the bottom row.
//
// inputs:
//       n - amount of characters to advance the cursor by.
//
void TextDisplay::AdvanceCursor(int n)
{
    _cursor_x += n;

    // divide by coloumns to get number of rows
    int r_count = _cursor_x / SYS::DISP::WIDTH;


    // if greater than 80, get number of rows and subtract that in 
    if(r_count){
        _cursor_x -= (SYS::DISP::WIDTH * r_count);

        // advance y for number
        _cursor_y += r_count;
    }

}

//----------------------------------------------------------------------------//
// Function: RetreatCursor
// desc: This function will move the cursor location backwards by the desired 
//       amount. it will wrap to the previous line if too long, and scroll the
//       screen up if past the top row.
//
// inputs:
//       n - amount of characters to retreat the cursor by.
//
void TextDisplay::RetreatCursor(int n)
{
}

//----------------------------------------------------------------------------//
// Function: UpdateCursor
// desc: This function will scroll the screen the required amount. Previous 
// text will be buffered to a certain limit - SCREEN_BUFFER_SIZE.
//
// inputs:
//       n - amount of rows to scroll the screen by. (+- up or down)
//
void TextDisplay::UpdateCursorFromConsole()
{
    int pos = SYS::DISP::CursorPosition();

    _cursor_y = pos / SYS::DISP::WIDTH;

    _cursor_x = pos - (_cursor_y * SYS::DISP::WIDTH);
}


// Function: UpdateCursor
// desc: This function will scroll the screen the required amount. Previous 
// text will be buffered to a certain limit - SCREEN_BUFFER_SIZE.
//
// inputs:
//       n - amount of rows to scroll the screen by. (+- up or down)
//
void TextDisplay::clear(){

    SYS::DISP::cls();
}