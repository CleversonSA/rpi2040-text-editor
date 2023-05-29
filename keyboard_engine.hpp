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


        KeyboardEngine();
        ~KeyboardEngine();

        KeyboardEngine & setCallbackfn(void (*fn)(const int, const char));
        KeyboardEngine & pressKey(const int, const char);


        virtual void setup() = 0;
        virtual void loop() = 0;

    private:

        void (*_callbackfn)(const int, const char);
};

#endif // DOCUMENT


