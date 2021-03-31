////////////////////////////////////////////////////////////////////////////////
// Title:           Text Display Class
// Filename:        TextDisplay.cpp
// Last Changed:    17/08/19
// Created:         17/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 00:07 17/08/19: Class created with default constructors.
//      - 00:07 17/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#ifndef APP_TEXTDISPLAY_H
#define APP_TEXTDISPLAY_H

class TextDisplay
{
public:
    TextDisplay();
    ~TextDisplay();

    void Print(const char* str, char colour = -1);
    void clear();

    void SetColour(char colour);

    void SetCursor(unsigned int x, unsigned int y);
    void AdvanceCursor(unsigned int n);
    void RetreatCursor(unsigned int n);


private:
    unsigned int _cursor_x, _cursor_y;
    char _colour;

    void UpdateCursorFromConsole();
};

#endif