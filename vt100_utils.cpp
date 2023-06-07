/*
    Copyright 2023 Cleverson S A

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <cstdio>
using std::sprintf;

#include <cstring>
using std::strcpy;

#include <iostream>
using std::cout;
using std::endl;

#include "vt100_utils.hpp"
#include "app_globals.hpp"

//*  ESC [ pn A        cursor up pn times - stop at top
char * VT100Utils::cursorMoveUp()
{
    char *str = new char[8];
    strcpy(str, "\033[1A");

    return (str);
}

//*  ESC [ pn B        cursor down pn times - stop at bottom
char * VT100Utils::cursorMoveDown()
{
    char *str = new char[8];
    strcpy(str, "\033[1B");

    return (str);
}

// *  ESC [ pn C        cursor right pn times - stop at far right
char * VT100Utils::cursorMoveRight()
{
    char *str = new char[8];
    strcpy(str, "\033[1C");

    return (str);
}


//*  ESC [ pn D        cursor left pn times - stop at far left
char * VT100Utils::cursorMoveLeft()
{
    char *str = new char[8];
    strcpy(str, "\033[1D");

    return (str);
}


//*  ESC [ pl ; pc H   set cursor position - pl Line, pc Column
char * VT100Utils::gotoXY(int x, int y)
{
    char *cmd = new char[32];

    sprintf(cmd,"\033[%d;%dH", x, y);

    return (cmd);
}


//*  ESC [ H           set cursor home
char * VT100Utils::cursorMoveHome()
{
    char *str = new char[8];
    strcpy(str, "\033[H");

    return (str);
}


//*  ESC E             next line (same as CR LF)
char * VT100Utils::lineBreak()
{
    char *str = new char[8];
    strcpy(str, "\033[E");

    return (str);
}



//*  ESC [ m           turn off attributes - normal video
char * VT100Utils::disableAttributes()
{
    char *str = new char[8];
    strcpy(str, "\033[m");

    return (str);
}

//*  ESC [ 4 m         turn on underline mode
char * VT100Utils::underlineAttribute()
{
    char *str = new char[8];
    strcpy(str, "\033[4m");

    return (str);
}

//*  ESC [ 7 m         turn on inverse video mode
char * VT100Utils::inverseAttribute()
{
    char *str = new char[8];
    strcpy(str, "\033[7m");

    return (str);
}

//*  ESC [ 1 m         highlight
char * VT100Utils::highlightAttribute()
{
    char *str = new char[8];
    strcpy(str, "\033[1m");

    return (str);
}

//*  ESC [ 5 m         blink
char * VT100Utils::blinkAttribute()
{
    char *str = new char[8];
    strcpy(str, "\033[5m");

    return (str);
}



//*  ESC [ 0 K         erase to end of line (inclusive)
char * VT100Utils::backspace()
{
    char *str = new char[8];
    strcpy(str, "\033[0K");

    return (str);
}

//*  ESC [ 2 K         erase entire line (cursor doesn't move)
char * VT100Utils::clearLine()
{
    char *str = new char[8];
    strcpy(str, "\033[2K");

    return (str);
}

//*  ESC [ 2 J         erase entire screen (cursor doesn't move)
char * VT100Utils::clearScreen()
{
    char *str = new char[8];
    strcpy(str, "\033[2J");

    return (str);
}

//*  ESC [ pt ; pb r   set scroll region
char * VT100Utils::setScrollRegion(int y1, int y2)
{
    char *cmd = new char[32];

    sprintf(cmd,"\033[%d;%dr", y1, y2);

    return (cmd);
}

//*  ESC [ ? 6 h       turn on region - origin mode
char * VT100Utils::scrollRegionOn()
{
    char *str = new char[9];
    strcpy(str, "\033[?6h");

    return (str);
}

//*  ESC [ ? 6 l       turn off region - full screen mode
char * VT100Utils::scrollRegionOff()
{
    char *str = new char[9];
    strcpy(str, "\033[?6l");

    return (str);
}



void VT100Utils::toString()
{
    cout << "[VT100Utils] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int VT100Utils::getMemSize()
{
    return sizeof((*this));
}


VT100Utils::~VT100Utils()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[VT100Utils] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

VT100Utils::VT100Utils():
CSAObject()
{

}



