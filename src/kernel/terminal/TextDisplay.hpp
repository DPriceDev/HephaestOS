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

    void Print(char* str, int colour = -1);
    void clear();

    void SetColour(int colour);

    void SetCursor(int x, int y);
    void AdvanceCursor(int n);
    void RetreatCursor(int n);


private:
    int _cursor_x, _cursor_y;
    int _colour;

    void UpdateCursorFromConsole();
};

#endif