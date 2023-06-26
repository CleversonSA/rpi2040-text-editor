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
#ifndef RPI2040USBKEYBOARD
#define RPI2040USBKEYBOARD

#include "app_globals.hpp"
#include "engine/keyboard_engine.hpp"

/* ----------------------- RPI PICO 2040 --------------------------------*/
#include "tusb.h"



/*
    RPI2040 USB Specific Keyboard Implementation.
*/
class Rpi2040UsbKeyboard: public KeyboardEngine
{
    public:

        ~Rpi2040UsbKeyboard();

        static Rpi2040UsbKeyboard & getInstance();

        void onUSBKeyboardEvent(hid_keyboard_report_t const *, hid_keyboard_report_t *);


        virtual void setup();
        virtual void loop();
        virtual void destroy();

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();

        int getESCFnCodes(const uint8_t[], int);
        int getESCExtraCodes(const uint8_t[], int);
        int getESCArrowCodes(const uint8_t[], int);
        int getSpecialCodes2(const uint8_t[], int);
        int getATildeMode(const uint8_t[], int);
        int getCuteMode(const uint8_t[], int);
        int getGraveMode(const uint8_t[], int);
        int getACircMode(const uint8_t[], int);
        int getNormalCode(hid_keyboard_report_t const *);


        virtual void setInterruptLoop(bool);
        virtual bool isInterruptLoop() const;

        virtual KeyboardEngine & setCallback(KeyboardCallback *);
        virtual KeyboardEngine & pressKey(const int, const char);

        virtual int parseRawKeycode(int, int);

    private:
        Rpi2040UsbKeyboard();

        static Rpi2040UsbKeyboard* _me;

        //Modifiers from TinyUsb
        int _lastModifier;
        int _lastRawKeyCode;

        bool _isTildeMode;
        bool _isGraveMode;
        bool _isCuteMode;
        bool _isACircMode;


        //From SDK Sample
        bool findKeyInReport(hid_keyboard_report_t *, uint8_t );

        //Allowed keys from SDK
        uint8_t const _keycode2ascii[128][2] = { HID_KEYCODE_TO_ASCII };



};

#endif // DOCUMENT





