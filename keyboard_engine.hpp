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
#ifndef KEYBOARDENGINE
#define KEYBOARDENGINE

#include "app_globals.hpp"
#include "csa_object.hpp"

/*
    Abstract class for agnostic keyboard input (may be a console, USB or Serial Keyboard)
*/
class KeyboardEngine: public CSAObject
{
    public:
        // Evens values to allow combinations
        static const int KEY_ANY      = 1;
        static const int KEY_ESCAPE   = 3;
        static const int KEY_TAB      = 5;
        static const int KEY_BACKSPACE= 7;
        static const int KEY_ENTER    = 9;
        static const int KEY_RCONTROL = 11;
        static const int KEY_LCONTROL = 13;
        static const int KEY_RSHIFT   = 15;
        static const int KEY_LSHIFT   = 17;
        static const int KEY_SPACE    = 19;
        static const int KEY_F1       = 21;
        static const int KEY_F2       = 23;
        static const int KEY_F3       = 25;
        static const int KEY_F4       = 27;
        static const int KEY_F5       = 29;
        static const int KEY_F6       = 31;
        static const int KEY_F7       = 33;
        static const int KEY_F8       = 35;
        static const int KEY_F9       = 37;
        static const int KEY_F10      = 39;
        static const int KEY_F11      = 41;
        static const int KEY_F12      = 43;
        static const int KEY_RALT     = 45;
        static const int KEY_LALT     = 47;
        static const int KEY_HOME     = 49;
        static const int KEY_END      = 51;
        static const int KEY_INS      = 53;
        static const int KEY_DEL      = 55;
        static const int KEY_PGUP     = 57;
        static const int KEY_PGDOWN   = 59;
        static const int KEY_UP       = 61;
        static const int KEY_DOWN     = 63;
        static const int KEY_LEFT     = 65;
        static const int KEY_RIGHT    = 67;
        static const int KEY_CCEDIL   = 68;

        static const int KEY_CEDILLA_UC_CODE = 69;
        static const int KEY_CEDILLA_LC_CODE = 70;
        static const int KEY_ATILDE_LC_CODE  = 71;
        static const int KEY_ATILDE_UC_CODE  = 72;
        static const int KEY_AGRAVE_LC_CODE  = 73;
        static const int KEY_AGRAVE_UC_CODE  = 74;
        static const int KEY_AACUTE_LC_CODE  = 75;
        static const int KEY_AACUTE_UC_CODE  = 76;
        static const int KEY_ACIRC_LC_CODE   = 77;
        static const int KEY_ACIRC_UC_CODE   = 78;
        static const int KEY_AUML_LC_CODE    = 79;
        static const int KEY_AUML_UC_CODE    = 80;
        static const int KEY_ARING_LC_CODE   = 81;
        static const int KEY_ARING_UC_CODE   = 82;
        static const int KEY_EGRAVE_LC_CODE  = 83;
        static const int KEY_EGRAVE_UC_CODE  = 84;
        static const int KEY_EACUTE_LC_CODE  = 85;
        static const int KEY_EACUTE_UC_CODE  = 86;
        static const int KEY_ECIRC_LC_CODE   = 87;
        static const int KEY_ECIRC_UC_CODE   = 88;
        static const int KEY_EUML_LC_CODE    = 89;
        static const int KEY_EUML_UC_CODE    = 90;
        static const int KEY_IGRAVE_LC_CODE  = 91;
        static const int KEY_IGRAVE_UC_CODE  = 92;
        static const int KEY_IACUTE_LC_CODE  = 93;
        static const int KEY_IACUTE_UC_CODE  = 94;
        static const int KEY_ICIRC_LC_CODE   = 95;
        static const int KEY_ICIRC_UC_CODE   = 96;
        static const int KEY_IUML_LC_CODE    = 97;
        static const int KEY_IUML_UC_CODE    = 98;
        static const int KEY_NTILDE_LC_CODE  = 99;
        static const int KEY_NTILDE_UC_CODE  = 100;
        static const int KEY_OGRAVE_LC_CODE  = 101;
        static const int KEY_OGRAVE_UC_CODE  = 102;
        static const int KEY_OACUTE_LC_CODE  = 103;
        static const int KEY_OACUTE_UC_CODE  = 104;
        static const int KEY_OCIRC_LC_CODE   = 105;
        static const int KEY_OCIRC_UC_CODE   = 106;
        static const int KEY_OTILDE_LC_CODE  = 107;
        static const int KEY_OTILDE_UC_CODE  = 108;
        static const int KEY_OUML_LC_CODE    = 109;
        static const int KEY_OUML_UC_CODE    = 110;
        static const int KEY_UGRAVE_LC_CODE  = 111;
        static const int KEY_UGRAVE_UC_CODE  = 112;
        static const int KEY_UACUTE_LC_CODE  = 113;
        static const int KEY_UACUTE_UC_CODE  = 114;
        static const int KEY_UCIRC_LC_CODE   = 115;
        static const int KEY_UCIRC_UC_CODE   = 116;
        static const int KEY_UUML_LC_CODE    = 117;
        static const int KEY_UUML_UC_CODE    = 118;

        static const int KEY_1RST_CODE       = 119;
        static const int KEY_2ND_CODE        = 120;
        static const int KEY_3RD_CODE        = 121;
        static const int KEY_EURO_CODE       = 122;
        static const int KEY_PARA_CODE       = 123;
        static const int KEY_DOTA_CODE       = 124;
        static const int KEY_GRAU_CODE       = 125;

        KeyboardEngine();
        ~KeyboardEngine();

        KeyboardEngine & setCallbackfn(bool (*fn)(const int, const char));
        KeyboardEngine & pressKey(const int, const char);


        virtual void setup() = 0;
        virtual void loop() = 0;
        virtual void destroy() = 0;

        virtual int parseRawKeycode(int, int) = 0;

    protected:


        void setInterruptLoop(bool);
        bool isInterruptLoop() const;
        bool (*_callbackfn)(const int, const char);
        bool _interruptLoop = false;



};

#endif // DOCUMENT


