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
#ifndef RPI2040UARTKEYBOARD
#define RPI2040UARTKEYBOARD

#include "app_globals.hpp"
#include "keyboard_engine.hpp"

/*
    RPI2040 UART Specific Keyboard Implementation.
*/
class Rpi2040UartKeyboard: public KeyboardEngine
{
    public:

        ~Rpi2040UartKeyboard();

        static Rpi2040UartKeyboard & getInstance();

        // This is called by the uart RPI lib
        static void onUartRXEvent();

        static inline uint8_t _uartBuffer[10] = {0,0,0,0,0,0,0,0,0,0};
        static int8_t  _uartBufferCounter;

        virtual void setup();
        virtual void loop();
        virtual void destroy();

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();

        int getESCFnCodes(uint8_t[], int );
        int getESCExtraCodes(uint8_t[], int );
        int getESCArrowCodes(uint8_t[], int );
        int getSpecialCodes1(uint8_t[], int );
        int getSpecialCodes2(uint8_t[], int );
        int getNormalCode(uint8_t[], int );

        virtual void setInterruptLoop(bool);
        virtual bool isInterruptLoop() const;

        virtual KeyboardEngine & setCallback(KeyboardCallback *);
        virtual KeyboardEngine & pressKey(const int, const char);

        virtual int parseRawKeycode(int, int);

    private:
        Rpi2040UartKeyboard();

        static Rpi2040UartKeyboard* _me;


};

#endif // DOCUMENT




