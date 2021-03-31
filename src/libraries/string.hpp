////////////////////////////////////////////////////////////////////////////////
// Title:           String Class and Functions
// Filename:        String.cpp
// Last Changed:    17/08/19
// Created:         17/08/19
// Author:          David Price
//
// Description:
//
//
//
// Changes:
//      - 02:10 17/08/19: Size function added and templated.
//      - 02:10 17/08/19: File Created.
////////////////////////////////////////////////////////////////////////////////
#ifndef SYS_STRING_H
#define SYS_STRING_H

namespace SYS
{
// Function: Size
// Desc: Used to get the size or length of an array.
//
// Inputs: 
//      str - a pointer to an array.
// Outputs: 
//      int - a int variable matching the array length.
//
template <typename T>
int Size(T str){

    int i(0);

    // count each character in the string.
    for (; str[i]; i++);

    return i;       // return count
}


//----------------------------------------------------------------------------//


// char* IntToCharArray(int i){

//     return "";
// }

// char* IntToString(int i){


// }

}

#endif