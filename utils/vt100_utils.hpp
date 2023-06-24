
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

/* Based on http://braun-home.net/michael/info/misc/VT100_commands.htm
    https://espterm.github.io/docs/VT100%20escape%20codes.html link */
#ifndef VT100UTILS
#define VT100UTILS

#include "../app_globals.hpp"
#include "../csa_object.hpp"

/*
    Just a utility to send ESC codes to Putty to emulate VT-100
*/
class VT100Utils: public CSAObject
{
    public:

        VT100Utils();
        ~VT100Utils();

        //*  ESC [ pn A        cursor up pn times - stop at top
        static char * cursorMoveUp();
        //*  ESC [ pn B        cursor down pn times - stop at bottom
        static char * cursorMoveDown();
        // *  ESC [ pn C        cursor right pn times - stop at far right
        static char * cursorMoveRight();
        //*  ESC [ pn D        cursor left pn times - stop at far left
        static char * cursorMoveLeft();
        //*  ESC [ pl ; pc H   set cursor position - pl Line, pc Column
        static char * gotoXY(int, int);
        //*  ESC [ H           set cursor home
        static char * cursorMoveHome();
        //*  ESC E             next line (same as CR LF)
        static char * lineBreak();


        //*  ESC [ m           turn off attributes - normal video
        static char * disableAttributes();
        //*  ESC [ 4 m         turn on underline mode
        static char * underlineAttribute();
        //*  ESC [ 7 m         turn on inverse video mode
        static char * inverseAttribute();
        //*  ESC [ 1 m         highlight
        static char * highlightAttribute();
        //*  ESC [ 5 m         blink
        static char * blinkAttribute();


        //*  ESC [ 0 K         erase to end of line (inclusive)
        static char * backspace();
        //*  ESC [ 2 K         erase entire line (cursor doesn't move)
        static char * clearLine();
        //*  ESC [ 2 J         erase entire screen (cursor doesn't move)
        static char * clearScreen();


        //*  ESC [ pt ; pb r   set scroll region
        static char * setScrollRegion(int, int);
        //*  ESC [ ? 6 h       turn on region - origin mode
        static char * scrollRegionOn();
        //*  ESC [ ? 6 l       turn off region - full screen mode
        static char * scrollRegionOff();


       virtual void toString(); // Yes, you know, Java feelings rs
       virtual int getMemSize();

};

#endif // DOCUMENT



