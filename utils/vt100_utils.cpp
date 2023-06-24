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
#include "../app_globals.hpp"

//*  ESC [ pn A        cursor up pn times - stop at top
char * VT100Utils::cursorMoveUp()
{
    static char str[] = "\033[1A";
    return (str);
}

//*  ESC [ pn B        cursor down pn times - stop at bottom
char * VT100Utils::cursorMoveDown()
{
    static char str2[] = "\033[1B";

    return (str2);
}

// *  ESC [ pn C        cursor right pn times - stop at far right
char * VT100Utils::cursorMoveRight()
{
    static char str3[] = "\033[1C";

    return (str3);
}


//*  ESC [ pn D        cursor left pn times - stop at far left
char * VT100Utils::cursorMoveLeft()
{
    static char str4[] = "\033[1D";

    return (str4);
}


//*  ESC [ pl ; pc H   set cursor position - pl Line, pc Column
char * VT100Utils::gotoXY(int x, int y)
{
    static char cmd[32];

    sprintf(cmd,"\033[%d;%dH", x, y);

    return (cmd);
}


//*  ESC [ H           set cursor home
char * VT100Utils::cursorMoveHome()
{
    static char str5[]="\033[H";

    return (str5);
}


//*  ESC E             next line (same as CR LF)
char * VT100Utils::lineBreak()
{
    static char str6[] = "\033[E";

    return (str6);
}



//*  ESC [ m           turn off attributes - normal video
char * VT100Utils::disableAttributes()
{
    static char str7[] = "\033[m";

    return (str7);
}

//*  ESC [ 4 m         turn on underline mode
char * VT100Utils::underlineAttribute()
{
    static char str8[] = "\033[4m";

    return (str8);
}

//*  ESC [ 7 m         turn on inverse video mode
char * VT100Utils::inverseAttribute()
{
    static char str9[] = "\033[7m";

    return (str9);
}

//*  ESC [ 1 m         highlight
char * VT100Utils::highlightAttribute()
{
    static char str10[] = "\033[1m";

    return (str10);
}

//*  ESC [ 5 m         blink
char * VT100Utils::blinkAttribute()
{
    static char str11[] = "\033[5m";

    return (str11);
}



//*  ESC [ 0 K         erase to end of line (inclusive)
char * VT100Utils::backspace()
{
    static char str12[] = "\033[0K";

    return (str12);
}

//*  ESC [ 2 K         erase entire line (cursor doesn't move)
char * VT100Utils::clearLine()
{
    static char str13[] = "\033[2K";

    return (str13);
}

//*  ESC [ 2 J         erase entire screen (cursor doesn't move)
char * VT100Utils::clearScreen()
{
    static char str14[] = "\033[2J";

    return (str14);
}

//*  ESC [ pt ; pb r   set scroll region
char * VT100Utils::setScrollRegion(int y1, int y2)
{
    static char cmd2[32];

    sprintf(cmd2,"\033[%d;%dr", y1, y2);

    return (cmd2);
}

//*  ESC [ ? 6 h       turn on region - origin mode
char * VT100Utils::scrollRegionOn()
{
    static char str15[] = "\033[?6h";

    return (str15);
}

//*  ESC [ ? 6 l       turn off region - full screen mode
char * VT100Utils::scrollRegionOff()
{
    static char str16[] = "\033[?6l";

    return (str16);
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



