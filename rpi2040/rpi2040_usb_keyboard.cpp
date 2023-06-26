
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



//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"


#define RECV_ESC_CODE           (41)
#define RECV_ENTER              (40)
#define RECV_BACKSPACE          (42)
#define RECV_TAB                (43)
#define RECV_SPACE              (44)

#define RECV_MOD_LSHIFT         (2)
#define RECV_MOD_RSHIFT         (32)
#define RECV_MOD_LCTRL          (1)
#define RECV_MOD_RCTRL          (16)
#define RECV_MOD_LALT           (4)
#define RECV_MOD_RALT           (64)

#define RECV_TILDE              (53)
#define RECV_CUTE               (52)
#define RECV_AGRAVE             (41)
#define RECV_ACIRC              (35)

#define WKTYPE_FN               (1000)
#define WKTYPE_EXTRA            (1001)
#define WKTYPE_ARROWS           (1002)
#define WKTYPE_SPECIAL_2        (1004)
#define WKTYPE_TILDE            (1005)
#define WKTYPE_ACUTE            (1006)
#define WKTYPE_AGRAVE           (1007)
#define WKTYPE_ACIRC            (1008)

#define F1_CODE                 (58)
#define F2_CODE                 (59)
#define F3_CODE                 (60)
#define F4_CODE                 (61)
#define F5_CODE                 (62)
#define F6_CODE                 (63)
#define F7_CODE                 (64)
#define F8_CODE                 (65)
#define F9_CODE                 (66)
#define F10_CODE                (67)
#define F11_CODE                (68)
#define F12_CODE                (69)

#define INS_CODE                (402)
#define HOME_CODE               (403)
#define PGUP_CODE               (404)
#define DELETE_CODE             (76)
#define END_CODE                (400)
#define PGDN_CODE               (401)

#define UP_CODE                 (82)
#define DN_CODE                 (81)
#define LEFT_CODE               (80)
#define RIGHT_CODE              (79)

#define CEDILLA_UC_CODE         (6)
#define CEDILLA_LC_CODE         (-6)
#define ATILDE_LC_CODE          (4)
#define ATILDE_UC_CODE          (-4)
#define AGRAVE_LC_CODE          (4)
#define AGRAVE_UC_CODE          (-4)
#define AACUTE_LC_CODE          (4)
#define AACUTE_UC_CODE          (-4)
#define ACIRC_LC_CODE           (4)
#define ACIRC_UC_CODE           (-4)
#define AUML_LC_CODE            (4)
#define AUML_UC_CODE            (-4)
#define ARING_LC_CODE           (4)
#define ARING_UC_CODE           (-4)
#define EGRAVE_LC_CODE          (8)
#define EGRAVE_UC_CODE          (-8)
#define EACUTE_LC_CODE          (8)
#define EACUTE_UC_CODE          (-8)
#define ECIRC_LC_CODE           (8)
#define ECIRC_UC_CODE           (-8)
#define EUML_LC_CODE            (8)
#define EUML_UC_CODE            (-8)
#define IGRAVE_LC_CODE          (12)
#define IGRAVE_UC_CODE          (-12)
#define IACUTE_LC_CODE          (12)
#define IACUTE_UC_CODE          (-12)
#define ICIRC_LC_CODE           (12)
#define ICIRC_UC_CODE           (-12)
#define IUML_LC_CODE            (12)
#define IUML_UC_CODE            (-12)
#define NTILDE_LC_CODE          (17)
#define NTILDE_UC_CODE          (-17)
#define OGRAVE_LC_CODE          (18)
#define OGRAVE_UC_CODE          (-18)
#define OACUTE_LC_CODE          (18)
#define OACUTE_UC_CODE          (-18)
#define OCIRC_LC_CODE           (18)
#define OCIRC_UC_CODE           (-18)
#define OTILDE_LC_CODE          (18)
#define OTILDE_UC_CODE          (-18)
#define OUML_LC_CODE            (18)
#define OUML_UC_CODE            (-18)
#define UGRAVE_LC_CODE          (24)
#define UGRAVE_UC_CODE          (-24)
#define UACUTE_LC_CODE          (24)
#define UACUTE_UC_CODE          (-24)
#define UCIRC_LC_CODE           (24)
#define UCIRC_UC_CODE           (-24)
#define UUML_LC_CODE            (24)
#define UUML_UC_CODE            (-24)

#define _1RST_CODE              (185)
#define _2ND_CODE               (178)
#define _3RD_CODE               (179)
#define EURO_CODE               (163)
#define PARA_CODE               (162)
#define DOTA_CODE               (170)
#define GRAU_CODE               (186)


#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <cstdio>
using std::sprintf;

#include <iomanip>
using std::setw;

#include "rpi2040/rpi2040_uart.hpp"
#include "app_globals.hpp"
#include "keyboard/keyboard_message.hpp"
#include "rpi2040_usb_keyboard.hpp"


/* ----------------------- RPI PICO 2040 --------------------------------*/
#include "bsp/board.h"
#include "tusb.h"

extern void hid_app_task(void);

Rpi2040UsbKeyboard * Rpi2040UsbKeyboard::_me = 0;




int Rpi2040UsbKeyboard::getACircMode(const uint8_t arr[], int length)
{
    if (!_isACircMode)
    {
        if(((int)arr[0] == RECV_ACIRC) && (_lastModifier == RECV_MOD_RSHIFT || _lastModifier == RECV_MOD_LSHIFT))
        {
            _isACircMode = true;
            KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            return 0;
        }
    } else {
        _isACircMode = false;
        switch((int)arr[0])
        {
            case ACIRC_LC_CODE:
            case ACIRC_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return ACIRC_UC_CODE;
                }
                return ACIRC_LC_CODE;
            case ECIRC_LC_CODE:
            case ECIRC_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return ECIRC_UC_CODE;
                }
                return ECIRC_LC_CODE;
            case ICIRC_LC_CODE:
            case ICIRC_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return ICIRC_UC_CODE;
                }
                return ICIRC_LC_CODE;
            case OCIRC_LC_CODE:
            case OCIRC_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return OCIRC_UC_CODE;
                }
                return OCIRC_LC_CODE;
            case UCIRC_LC_CODE:
            case UCIRC_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return UCIRC_UC_CODE;
                }
                return UCIRC_LC_CODE;
            case RECV_ACIRC:
                return RECV_ACIRC;
            default:
                return (int)arr[0];
        }
    }
    return 0;
}


int Rpi2040UsbKeyboard::getGraveMode(const uint8_t arr[], int length)
{
    if (!_isGraveMode)
    {
        if(((int)arr[0] == RECV_AGRAVE) && (_lastModifier == RECV_MOD_RALT))
        {
            _isGraveMode = true;
            KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            return 0;
        }
    } else {
        _isGraveMode = false;
        switch((int)arr[0])
        {
            case AGRAVE_UC_CODE:
            case AGRAVE_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return AGRAVE_UC_CODE;
                }
                return AGRAVE_LC_CODE;
            case EGRAVE_UC_CODE:
            case EGRAVE_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return EGRAVE_UC_CODE;
                }
                return EGRAVE_UC_CODE;
            case IGRAVE_UC_CODE:
            case IGRAVE_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return IGRAVE_UC_CODE;
                }
                return IGRAVE_LC_CODE;
            case OGRAVE_UC_CODE:
            case OGRAVE_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return OGRAVE_UC_CODE;
                }
                return OGRAVE_LC_CODE;
            case UGRAVE_UC_CODE:
            case UGRAVE_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return UGRAVE_UC_CODE;
                }
                return UGRAVE_LC_CODE;
            case RECV_AGRAVE:
                return RECV_AGRAVE;
            default:
                return (int)arr[0];
        }
    }
    return 0;
}


int Rpi2040UsbKeyboard::getCuteMode(const uint8_t arr[], int length)
{
    if (!_isCuteMode)
    {
        if((int)arr[0] == RECV_CUTE)
        {
            _isCuteMode = true;
            KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            return 0;
        }
    } else {
        _isCuteMode = false;
        switch((int)arr[0])
        {
            case AACUTE_LC_CODE:
            case AACUTE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return AACUTE_UC_CODE;
                }
                return AACUTE_LC_CODE;
            case EACUTE_LC_CODE:
            case EACUTE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return EACUTE_UC_CODE;
                }
                return EACUTE_LC_CODE;
            case IACUTE_LC_CODE:
            case IACUTE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return IACUTE_UC_CODE;
                }
                return IACUTE_UC_CODE;
            case OACUTE_LC_CODE:
            case OACUTE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return OACUTE_UC_CODE;
                }
                return OACUTE_LC_CODE;
            case UACUTE_LC_CODE:
            case UACUTE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return UACUTE_UC_CODE;
                }
                return UACUTE_LC_CODE;
            case CEDILLA_UC_CODE:
            case CEDILLA_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return CEDILLA_UC_CODE;
                }
                return CEDILLA_LC_CODE;
            case RECV_TILDE:
                return RECV_TILDE;
            default:
                return (int)arr[0];
        }
    }
    return 0;
}

int Rpi2040UsbKeyboard::getATildeMode(const uint8_t arr[], int length)
{
    if (!_isTildeMode)
    {
        if((int)arr[0] == RECV_TILDE)
        {
            _isTildeMode = true;
            KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            return 0;
        }
    } else {
        _isTildeMode = false;
        switch((int)arr[0])
        {
            case ATILDE_UC_CODE:
            case ATILDE_LC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return ATILDE_UC_CODE;
                }
                return ATILDE_LC_CODE;
            case NTILDE_LC_CODE:
            case NTILDE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return NTILDE_UC_CODE;
                }
                return NTILDE_LC_CODE;
            case OTILDE_LC_CODE:
            case OTILDE_UC_CODE:
                if (_lastModifier == RECV_MOD_LSHIFT || _lastModifier == RECV_MOD_RSHIFT )
                {
                    return OTILDE_UC_CODE;
                }
                return OTILDE_LC_CODE;
            default:
                return (int)arr[0];
        }
    }
    return 0;
}

int Rpi2040UsbKeyboard::getESCExtraCodes(const uint8_t arr[], int length)
{

    switch((int)arr[0])
    {
        case HOME_CODE:
        case INS_CODE:
        case END_CODE:
        case PGDN_CODE:
        case PGUP_CODE:
        case DELETE_CODE:
            return (int)arr[0];
        default:
            return 0;
    }

    return 0;
}


int Rpi2040UsbKeyboard::getESCFnCodes(const uint8_t arr[], int length)
{
    switch((int)arr[0])
    {
        case F1_CODE:
        case F2_CODE:
        case F3_CODE:
        case F4_CODE:
        case F5_CODE:
        case F6_CODE:
        case F7_CODE:
        case F8_CODE:
        case F9_CODE:
        case F10_CODE:
        case F11_CODE:
        case F12_CODE:
            return (int)arr[0];
        default:
            return 0;
    }
    return 0;
}


int Rpi2040UsbKeyboard::getESCArrowCodes(const uint8_t arr[], int length)
{
    switch((int)arr[0])
    {
        case UP_CODE:
        case DN_CODE:
        case LEFT_CODE:
        case RIGHT_CODE:
            return (int)arr[0];
        default:
            return 0;
    }
    return 0;
}



int Rpi2040UsbKeyboard::getSpecialCodes2(const uint8_t arr[], int length)
{
    switch((int)arr[0])
    {
        case _1RST_CODE:
        case _2ND_CODE:
        case _3RD_CODE:
        case EURO_CODE:
        case PARA_CODE:
        case DOTA_CODE:
        case GRAU_CODE:
        case RECV_ESC_CODE:
        case RECV_ENTER:
        case RECV_BACKSPACE:
        case RECV_TAB:
        case RECV_SPACE:
            return (int)arr[0];
        default:
            return 0;
    }
    return 0;
}


int Rpi2040UsbKeyboard::getNormalCode(hid_keyboard_report_t const *report)
{
    cout << "report = " <<(int) (*report).keycode[0] << endl;
    switch((int)(*report).keycode[0])
    {
        case RECV_ESC_CODE:
        case RECV_ENTER:
        case RECV_BACKSPACE:
        case RECV_TAB:
        case RECV_SPACE:
            return (int)(*report).keycode[0];
        default:
            // not existed in previous report means the current key is pressed
            bool const is_shift = (*report).modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT);
            uint8_t readCode = _keycode2ascii[(*report).keycode[0]][is_shift ? 1 : 0];
            return (int)readCode;
    }

}


Rpi2040UsbKeyboard& Rpi2040UsbKeyboard::getInstance()
{
    if (Rpi2040UsbKeyboard::_me == 0)
    {
        Rpi2040UsbKeyboard::_me = new Rpi2040UsbKeyboard();
    }
    return (*Rpi2040UsbKeyboard::_me);
}


// look up new key in previous keys
bool Rpi2040UsbKeyboard::findKeyInReport(hid_keyboard_report_t  *report, uint8_t keycode)
{
  for(uint8_t i=0; i<6; i++)
  {
    if ((*report).keycode[i] == keycode)
        return true;
  }

  return false;
}


void Rpi2040UsbKeyboard::onUSBKeyboardEvent(hid_keyboard_report_t const *usbKbReport, hid_keyboard_report_t *usbKbPreviousReport)
{

  char tmp[32];
  int readCode;
  bool charRecognized = false;


    if ( (*usbKbReport).keycode[0] )
    {
        // As SDK Sample says, may be the char is in holding mode
        if (findKeyInReport(usbKbPreviousReport, (*usbKbReport).keycode[0]))
        {
            return;
        }

        _lastModifier = (*usbKbReport).modifier;

        readCode = Rpi2040UsbKeyboard::getInstance().getESCFnCodes((*usbKbReport).keycode,6);
        if (readCode > 0 && !_isTildeMode &&!_isCuteMode &&!_isGraveMode && !_isACircMode ) {
             KeyboardMessage::getInstance()._rawCode =  '\0';
             KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_FN,readCode);
             KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
             cout << "WKTYPE_FN!" << endl;

             charRecognized = true;
        }


        if (!charRecognized  && !_isTildeMode &&!_isCuteMode &&!_isGraveMode  ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getACircMode((*usbKbReport).keycode,6);
            if (readCode != 0) {
                KeyboardMessage::getInstance()._rawCode =  '\0';
                KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_ACIRC,readCode);
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                cout << "WKTYPE_ACIRC!" << endl;
                charRecognized = true;
            } else if (readCode == 0) {
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            }
        }

        if (!charRecognized  && !_isTildeMode &&!_isCuteMode  && !_isACircMode ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getGraveMode((*usbKbReport).keycode,6);
            if (readCode != 0) {
                KeyboardMessage::getInstance()._rawCode =  '\0';
                KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_AGRAVE,readCode);
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                cout << "WKTYPE_AGRAVE!" << endl;
                charRecognized = true;
            } else if (readCode == 0) {
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            }
        }

        if (!charRecognized  && !_isTildeMode &&!_isGraveMode && !_isACircMode ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getCuteMode((*usbKbReport).keycode,6);
            if (readCode != 0) {
                KeyboardMessage::getInstance()._rawCode =  '\0';
                KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_ACUTE,readCode);
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                cout << "WKTYPE_ACUTE!" << endl;
                charRecognized = true;
            } else if (readCode == 0) {
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            }
        }

        if (!charRecognized  &&!_isCuteMode &&!_isGraveMode && !_isACircMode  ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getATildeMode((*usbKbReport).keycode,6);
            if (readCode != 0) {
                KeyboardMessage::getInstance()._rawCode =  '\0';
                KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_TILDE,readCode);
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                cout << "WKTYPE_ATILDE!" << endl;
                charRecognized = true;
            } else if (readCode == 0) {
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 1;
            }
        }

        if (!charRecognized  && !_isTildeMode &&!_isCuteMode &&!_isGraveMode && !_isACircMode ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getESCArrowCodes((*usbKbReport).keycode,6);
            if (readCode > 0) {
                 KeyboardMessage::getInstance()._rawCode =  '\0';
                 KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_ARROWS,readCode);
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                 cout << "WKTYPE_ARROWS!" << endl;
                 charRecognized = true;
            }
        }

        if (!charRecognized  && !_isTildeMode &&!_isCuteMode &&!_isGraveMode && !_isACircMode ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getSpecialCodes2((*usbKbReport).keycode,6);
            if (readCode > 0) {
                 KeyboardMessage::getInstance()._rawCode =  '\0';
                 KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_SPECIAL_2,readCode);
                 KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                 cout << "WKTYPE_SPECIAL_2!" << endl;
                 charRecognized = true;
            }
        }

        if (!charRecognized  && !_isTildeMode &&!_isCuteMode &&!_isGraveMode  && !_isACircMode  ) {
            readCode = Rpi2040UsbKeyboard::getInstance().getESCExtraCodes((*usbKbReport).keycode,6);

            if (readCode > 0) {
                 KeyboardMessage::getInstance()._rawCode =  '\0';
                 KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(WKTYPE_EXTRA,readCode);
                 KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;
                cout << "WKTYPE_EXTRA!" << endl;
                 charRecognized = true;
            }
        }


        if (!charRecognized  && !_isTildeMode &&!_isCuteMode &&!_isGraveMode && !_isACircMode  ) {

            readCode = Rpi2040UsbKeyboard::getInstance().getNormalCode(usbKbReport);
            if (readCode > 0) {
                KeyboardMessage::getInstance()._rawCode =  (char)readCode;
                KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UsbKeyboard::getInstance().parseRawKeycode(-1,readCode);
                KeyboardMessage::getInstance()._qtIgnoreKeyPress = 0;

                cout << "qualquer!" << endl;
                charRecognized = false;
            }
        }

        //Logica das teclas;
        KeyboardMessage::getInstance()._sharedInterruptedLoop = true;

       /*sprintf(tmp, "[%d,%d,%d,%d,%d,%d,%d]",
              (*usbKbReport).keycode[0],
              (*usbKbReport).keycode[1],
              (*usbKbReport).keycode[2],
              (*usbKbReport).keycode[3],
              (*usbKbReport).keycode[4],
              (*usbKbReport).keycode[5],
              (*usbKbReport).modifier
              );
        uart_puts(Rpi2040Uart::getInstance().getUart(), tmp);*/

        fflush(stdout); // flush right away, else nanolib will wait for newline

        //KeyboardMessage::getInstance()._sharedInterruptedLoop = true;


    }
}


void Rpi2040UsbKeyboard::setup()
{

     // init host stack on configured roothub port
    tuh_init(BOARD_TUH_RHPORT);

    KeyboardMessage::getInstance()._rawCode='\0';
    KeyboardMessage::getInstance()._sharedInterruptedLoop=false;
    KeyboardMessage::getInstance()._keyboardKeyCode=-1;

}

void Rpi2040UsbKeyboard::setInterruptLoop(bool interruptLoop)
{
    /* Unfortunately, the IRQ Handler lost the callback info, so I have to
        use a 3rd class to handle it in other location of memory, bizarre! */
    KeyboardMessage::getInstance()._sharedInterruptedLoop = interruptLoop;

}

bool Rpi2040UsbKeyboard::isInterruptLoop() const
{
    /* Unfortunately, the IRQ Handler lost the callback info, so I have to
        use a 3rd class to handle it in other location of memory, bizarre! */
    return (KeyboardMessage::getInstance()._sharedInterruptedLoop);
}


KeyboardEngine & Rpi2040UsbKeyboard:: setCallback(KeyboardCallback *keyboardCallback)
{
    /* Unfortunately, the IRQ Handler lost the callback info, so I have to
        use a 3rd class to handle it in other location of memory, bizarre! */
    KeyboardMessage::getInstance()._sharedCallback = keyboardCallback;


    return (*this);
}

KeyboardEngine & Rpi2040UsbKeyboard::pressKey(const int keyCode, const char rawChar)
{
    if (KeyboardMessage::getInstance()._sharedCallback == 0)
    {
        return (*this);
    }

    //cout << "Key Pressed: keyboard_engine_code = [" << keyCode << "] rawchar=[" << rawChar << "]" << endl;
    setInterruptLoop((*KeyboardMessage::getInstance()._sharedCallback).execute(keyCode, rawChar));

    return (*this);
}


int Rpi2040UsbKeyboard::parseRawKeycode(int rawKeyType, int rawKeyCode)
{
    if (rawKeyType == WKTYPE_FN)
    {
        switch(rawKeyCode)
        {
        case F1_CODE: return KeyboardEngine::KEY_F1;
        case F2_CODE: return KeyboardEngine::KEY_F2;
        case F3_CODE: return KeyboardEngine::KEY_F3;
        case F4_CODE: return KeyboardEngine::KEY_F4;
        case F5_CODE: return KeyboardEngine::KEY_F5;
        case F6_CODE: return KeyboardEngine::KEY_F6;
        case F7_CODE: return KeyboardEngine::KEY_F7;
        case F8_CODE: return KeyboardEngine::KEY_F8;
        case F9_CODE: return KeyboardEngine::KEY_F9;
        case F10_CODE: return KeyboardEngine::KEY_F10;
        case F11_CODE: return KeyboardEngine::KEY_F11;
        case F12_CODE: return KeyboardEngine::KEY_F12;
        default:
            return KeyboardEngine::KEY_F1;
        }
    } else if (rawKeyType == WKTYPE_ARROWS){
        switch(rawKeyCode)
        {
        case UP_CODE:    return KeyboardEngine::KEY_UP;
        case DN_CODE:    return KeyboardEngine::KEY_DOWN;
        case LEFT_CODE:  return KeyboardEngine::KEY_LEFT;
        case RIGHT_CODE: return KeyboardEngine::KEY_RIGHT;
        default:
            return KeyboardEngine::KEY_ANY;
        }
    } else if (rawKeyType == WKTYPE_EXTRA){
        switch(rawKeyCode)
        {
        case INS_CODE:    return KeyboardEngine::KEY_INS;
        case HOME_CODE:   return KeyboardEngine::KEY_HOME;
        case PGUP_CODE:   return KeyboardEngine::KEY_PGUP;
        case END_CODE:    return KeyboardEngine::KEY_END;
        case DELETE_CODE: return KeyboardEngine::KEY_DEL;
        default:
            return KeyboardEngine::KEY_HOME;
        }
    } else if (rawKeyType == WKTYPE_SPECIAL_2) {
        switch (rawKeyCode) {

            case _1RST_CODE:
                return KeyboardEngine::KEY_1RST_CODE;
            case _2ND_CODE:
                return KeyboardEngine::KEY_2ND_CODE;
            case _3RD_CODE:
                return KeyboardEngine::KEY_3RD_CODE;
            case EURO_CODE:
                return KeyboardEngine::KEY_EURO_CODE;
            case PARA_CODE:
                return KeyboardEngine::KEY_PARA_CODE;
            case DOTA_CODE:
                return KeyboardEngine::KEY_DOTA_CODE;
            case GRAU_CODE:
                return KeyboardEngine::KEY_GRAU_CODE;
            case RECV_ESC_CODE:
                return KeyboardEngine::KEY_ESCAPE;
            case RECV_ENTER:
                return KeyboardEngine::KEY_ENTER;
            case RECV_BACKSPACE:
                return KeyboardEngine::KEY_BACKSPACE;
            case RECV_TAB:
                return KeyboardEngine::KEY_TAB;
            case RECV_SPACE:
                return KeyboardEngine::KEY_SPACE;
            default:
                return KeyboardEngine::KEY_ANY;

        }
    } else if (rawKeyType == WKTYPE_TILDE) {
        switch(rawKeyCode)
        {
            case ATILDE_LC_CODE:
                return KeyboardEngine::KEY_ATILDE_LC_CODE;
            case ATILDE_UC_CODE:
                return KeyboardEngine::KEY_ATILDE_UC_CODE;
            case OTILDE_LC_CODE:
                return KeyboardEngine::KEY_OTILDE_LC_CODE;
            case OTILDE_UC_CODE:
                return KeyboardEngine::KEY_OTILDE_UC_CODE;
            case NTILDE_LC_CODE:
                return KeyboardEngine::KEY_NTILDE_LC_CODE;
            case NTILDE_UC_CODE:
                return KeyboardEngine::KEY_NTILDE_UC_CODE;
            case RECV_TILDE:
                return KeyboardEngine::KEY_TILDE;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    } else if (rawKeyType == WKTYPE_ACUTE) {
        switch(rawKeyCode)
        {
            case AACUTE_LC_CODE:
                return KeyboardEngine::KEY_AACUTE_LC_CODE;
            case AACUTE_UC_CODE:
                return KeyboardEngine::KEY_AACUTE_UC_CODE;
            case EACUTE_LC_CODE:
                return KeyboardEngine::KEY_EACUTE_LC_CODE;
            case EACUTE_UC_CODE:
                return KeyboardEngine::KEY_EACUTE_UC_CODE;
            case IACUTE_UC_CODE:
                return KeyboardEngine::KEY_IACUTE_LC_CODE;
            case IACUTE_LC_CODE:
                return KeyboardEngine::KEY_IACUTE_LC_CODE;
            case OACUTE_LC_CODE:
                return KeyboardEngine::KEY_OACUTE_LC_CODE;
            case OACUTE_UC_CODE:
                return KeyboardEngine::KEY_OACUTE_UC_CODE;
            case UACUTE_LC_CODE:
                return KeyboardEngine::KEY_UACUTE_LC_CODE;
            case UACUTE_UC_CODE:
                return KeyboardEngine::KEY_UACUTE_UC_CODE;
            case CEDILLA_LC_CODE:
                return KeyboardEngine::KEY_CEDILLA_LC_CODE;
            case CEDILLA_UC_CODE:
                return KeyboardEngine::KEY_CEDILLA_UC_CODE;
            case RECV_CUTE:
                return KeyboardEngine::KEY_ACUTE;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    } else if (rawKeyType == WKTYPE_AGRAVE) {
        switch(rawKeyCode)
        {
            case AGRAVE_LC_CODE:
                return KeyboardEngine::KEY_AGRAVE_LC_CODE;
            case AGRAVE_UC_CODE:
                return KeyboardEngine::KEY_AGRAVE_UC_CODE;
            case EGRAVE_LC_CODE:
                return KeyboardEngine::KEY_EGRAVE_LC_CODE;
            case EGRAVE_UC_CODE:
                return KeyboardEngine::KEY_EGRAVE_UC_CODE;
            case IGRAVE_LC_CODE:
                return KeyboardEngine::KEY_IGRAVE_LC_CODE;
            case IGRAVE_UC_CODE:
                return KeyboardEngine::KEY_IGRAVE_UC_CODE;
            case OGRAVE_LC_CODE:
                return KeyboardEngine::KEY_OGRAVE_LC_CODE;
            case OGRAVE_UC_CODE:
                return KeyboardEngine::KEY_OGRAVE_UC_CODE;
            case UGRAVE_LC_CODE:
                return KeyboardEngine::KEY_UGRAVE_LC_CODE;
            case UGRAVE_UC_CODE:
                return KeyboardEngine::KEY_UGRAVE_UC_CODE;
            case RECV_AGRAVE:
                return KeyboardEngine::KEY_AGRAVE;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    } else if (rawKeyType == WKTYPE_ACIRC) {
        switch(rawKeyCode)
        {
            case ACIRC_LC_CODE:
                return KeyboardEngine::KEY_ACIRC_LC_CODE;
            case ACIRC_UC_CODE:
                return KeyboardEngine::KEY_ACIRC_UC_CODE;
            case ECIRC_LC_CODE:
                return KeyboardEngine::KEY_ECIRC_LC_CODE;
            case ECIRC_UC_CODE:
                return KeyboardEngine::KEY_ECIRC_UC_CODE;
            case ICIRC_LC_CODE:
                return KeyboardEngine::KEY_ICIRC_LC_CODE;
            case ICIRC_UC_CODE:
                return KeyboardEngine::KEY_ICIRC_UC_CODE;
            case OCIRC_LC_CODE:
                return KeyboardEngine::KEY_OCIRC_LC_CODE;
            case OCIRC_UC_CODE:
                return KeyboardEngine::KEY_OCIRC_UC_CODE;
            case UCIRC_LC_CODE:
                return KeyboardEngine::KEY_UCIRC_LC_CODE;
            case UCIRC_UC_CODE:
                return KeyboardEngine::KEY_UCIRC_UC_CODE;
            case RECV_ACIRC:
                return KeyboardEngine::KEY_ACIRC;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    } else {
        cout << rawKeyCode << endl;
        return KeyboardEngine::KEY_ANY;
    }
}


void Rpi2040UsbKeyboard::loop()
{

    while (!isInterruptLoop()) {

        while (!isInterruptLoop())
        {
            //tight_loop_contents();

            // tinyusb host task
            tuh_task();
            hid_app_task();
        }

        //The callback function will decide if loop stops or not! Look KeyboardMessage
        cout << "ignore key press = " << KeyboardMessage::getInstance()._qtIgnoreKeyPress << endl;
        if (KeyboardMessage::getInstance()._qtIgnoreKeyPress == 0) {
            pressKey(KeyboardMessage::getInstance()._keyboardKeyCode,
                     KeyboardMessage::getInstance()._rawCode);
        } else {
            KeyboardMessage::getInstance()._sharedInterruptedLoop = false;
        }
    }

}


void  Rpi2040UsbKeyboard::destroy()
{

}

void Rpi2040UsbKeyboard::toString()
{
    cout << "[Rpi2040UsbKeyboard] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
        << endl;
}

int Rpi2040UsbKeyboard::getMemSize()
{
    return sizeof((*this));
}

Rpi2040UsbKeyboard::~Rpi2040UsbKeyboard()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040UsbKeyboard] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040UsbKeyboard::Rpi2040UsbKeyboard():
KeyboardEngine(),
_lastModifier(0),
_lastRawKeyCode(0),
_isTildeMode(false),
_isGraveMode(false),
_isCuteMode(false)
{

}



