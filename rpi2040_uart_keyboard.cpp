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


#define RECV_ESC_CODE           (27)
#define RECV_SPECIAL_1_CODE     (195)
#define RECV_SPECIAL_2_CODE     (194)
#define RECV_BEGIN_ESC_CODE     (91)
#define RECV_OPT_END_ESC_CODE   (126)
#define RECV_1_CODE             (49)
#define RECV_2_CODE             (50)
#define RECV_3_CODE             (51)
#define RECV_4_CODE             (52)
#define RECV_5_CODE             (53)
#define RECV_6_CODE             (54)
#define RECV_7_CODE             (55)
#define RECV_8_CODE             (56)
#define RECV_9_CODE             (57)
#define RECV_0_CODE             (48)
#define RECV_ENTER              (13)
#define RECV_BACKSPACE          (127)
#define RECV_TAB                (9)
#define RECV_SPACE              (32)


#define WKTYPE_FN               (1000)
#define WKTYPE_EXTRA            (1001)
#define WKTYPE_ARROWS           (1002)
#define WKTYPE_SPECIAL_1        (1003)
#define WKTYPE_SPECIAL_2        (1004)

#define F1_CODE                 (11)
#define F2_CODE                 (12)
#define F3_CODE                 (13)
#define F4_CODE                 (14)
#define F5_CODE                 (15)
#define F6_CODE                 (17)
#define F7_CODE                 (18)
#define F8_CODE                 (19)
#define F9_CODE                 (20)
#define F10_CODE                (21)
#define F11_CODE                (23)
#define F12_CODE                (24)

#define INS_CODE                (2)
#define HOME_CODE               (1)
#define PGUP_CODE               (5)
#define DELETE_CODE             (3)
#define END_CODE                (4)
#define PGDN_CODE               (6)

#define UP_CODE                 (65)
#define DN_CODE                 (66)
#define LEFT_CODE               (68)
#define RIGHT_CODE              (67)

#define CEDILLA_UC_CODE         (135)
#define CEDILLA_LC_CODE         (167)
#define ATILDE_LC_CODE          (163)
#define ATILDE_UC_CODE          (131)
#define AGRAVE_LC_CODE          (160)
#define AGRAVE_UC_CODE          (128)
#define AACUTE_LC_CODE          (161)
#define AACUTE_UC_CODE          (129)
#define ACIRC_LC_CODE           (162)
#define ACIRC_UC_CODE           (130)
#define AUML_LC_CODE            (164)
#define AUML_UC_CODE            (132)
#define ARING_LC_CODE           (-1)
#define ARING_UC_CODE           (-2)
#define EGRAVE_LC_CODE          (168)
#define EGRAVE_UC_CODE          (136)
#define EACUTE_LC_CODE          (169)
#define EACUTE_UC_CODE          (137)
#define ECIRC_LC_CODE           (170)
#define ECIRC_UC_CODE           (138)
#define EUML_LC_CODE            (171)
#define EUML_UC_CODE            (139)
#define IGRAVE_LC_CODE          (172)
#define IGRAVE_UC_CODE          (140)
#define IACUTE_LC_CODE          (173)
#define IACUTE_UC_CODE          (141)
#define ICIRC_LC_CODE           (174)
#define ICIRC_UC_CODE           (142)
#define IUML_LC_CODE            (175)
#define IUML_UC_CODE            (143)
#define NTILDE_LC_CODE          (177)
#define NTILDE_UC_CODE          (145)
#define OGRAVE_LC_CODE          (178)
#define OGRAVE_UC_CODE          (146)
#define OACUTE_LC_CODE          (179)
#define OACUTE_UC_CODE          (147)
#define OCIRC_LC_CODE           (180)
#define OCIRC_UC_CODE           (148)
#define OTILDE_LC_CODE          (181)
#define OTILDE_UC_CODE          (149)
#define OUML_LC_CODE            (182)
#define OUML_UC_CODE            (150)
#define UGRAVE_LC_CODE          (185)
#define UGRAVE_UC_CODE          (153)
#define UACUTE_LC_CODE          (186)
#define UACUTE_UC_CODE          (154)
#define UCIRC_LC_CODE           (187)
#define UCIRC_UC_CODE           (155)
#define UUML_LC_CODE            (188)
#define UUML_UC_CODE            (156)

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

#include <iomanip>
using std::setw;

#include "rpi2040_uart_keyboard.hpp"
#include "rpi2040_uart.hpp"
#include "app_globals.hpp"
#include "VT100_utils.hpp"
#include "keyboard_message.hpp"

Rpi2040UartKeyboard * Rpi2040UartKeyboard::_me = 0;
int8_t  Rpi2040UartKeyboard::_uartBufferCounter = 0;

int Rpi2040UartKeyboard::getESCExtraCodes(uint8_t arr[], int length)
{
    //Starts with ESC[
    if ((length > 2) && arr[0] == (uint8_t)RECV_ESC_CODE && arr[1] == (uint8_t)RECV_BEGIN_ESC_CODE )
    {
        if((length >= 3) && (arr[length - 1] == (uint8_t)RECV_OPT_END_ESC_CODE)) {
            char values[32];
            int vcount = 0;
            for (int i=2; i < length; i++)
            {
                values[vcount] = (char)arr[i];
                vcount++;
            }
            int valorConv = atoi(values);

            switch(valorConv)
            {
            case HOME_CODE:
            case LEFT_CODE:
            case INS_CODE:
            case END_CODE:
            case PGDN_CODE:
            case PGUP_CODE:
            case DELETE_CODE:
                return valorConv;
            default:
                return 0;
            }
        }
   }
    return 0;
}


int Rpi2040UartKeyboard::getESCFnCodes(uint8_t arr[], int length)
{
    //Starts with ESC[
    if ((length > 2) && arr[0] == (uint8_t)RECV_ESC_CODE && arr[1] == (uint8_t)RECV_BEGIN_ESC_CODE )
    {
        if((length >= 3) && (arr[length - 1] == (uint8_t)RECV_OPT_END_ESC_CODE)) {
            char values[32];
            int vcount = 0;
            for (int i=2; i < length; i++)
            {
                values[vcount] = (char)arr[i];
                vcount++;
            }
            int valorConv = atoi(values);


            switch(valorConv)
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
                    return valorConv;
                default:
                    return 0;
            }
        }
   }
    return 0;
}


int Rpi2040UartKeyboard::getESCArrowCodes(uint8_t arr[], int length)
{
    //Starts with ESC[
    if ((length > 2) && arr[0] == (uint8_t)RECV_ESC_CODE && arr[1] == (uint8_t)RECV_BEGIN_ESC_CODE )
    {
        if((length >= 3) && (arr[length - 1] != (uint8_t)RECV_OPT_END_ESC_CODE)) {
            switch(arr[2])
            {
                case UP_CODE:
                case DN_CODE:
                case LEFT_CODE:
                case RIGHT_CODE:
                    return (int)arr[2];
                default:
                    return 0;
            }
        }
   }
    return 0;
}


int Rpi2040UartKeyboard::getSpecialCodes1(uint8_t arr[], int length)
{
    //Starts with ESC[
    if ((length > 2) && arr[0] == (uint8_t)RECV_SPECIAL_1_CODE)
    {
        if((length >= 3)) {
            char values[32];
            int vcount = 0;
            for (int i=2; i < length; i++)
            {
                values[vcount] = (char)arr[i];
                vcount++;
            }
            int valorConv = atoi(values);

            switch(valorConv)
            {
                case CEDILLA_LC_CODE:
                case ATILDE_LC_CODE:
                case ATILDE_UC_CODE:
                case AGRAVE_LC_CODE:
                case AGRAVE_UC_CODE:
                case AACUTE_LC_CODE:
                case AACUTE_UC_CODE:
                case ACIRC_LC_CODE:
                case ACIRC_UC_CODE:
                case AUML_LC_CODE:
                case AUML_UC_CODE:
                case ARING_LC_CODE:
                case ARING_UC_CODE:
                case EGRAVE_LC_CODE:
                case EGRAVE_UC_CODE:
                case EACUTE_LC_CODE:
                case EACUTE_UC_CODE:
                case ECIRC_LC_CODE:
                case ECIRC_UC_CODE:
                case EUML_LC_CODE:
                case EUML_UC_CODE:
                case IGRAVE_LC_CODE:
                case IGRAVE_UC_CODE:
                case IACUTE_LC_CODE:
                case IACUTE_UC_CODE:
                case ICIRC_LC_CODE:
                case ICIRC_UC_CODE:
                case IUML_LC_CODE:
                case IUML_UC_CODE:
                case NTILDE_LC_CODE:
                case NTILDE_UC_CODE:
                case OGRAVE_LC_CODE:
                case OGRAVE_UC_CODE:
                case OACUTE_LC_CODE:
                case OACUTE_UC_CODE:
                case OCIRC_LC_CODE:
                case OCIRC_UC_CODE:
                case OTILDE_LC_CODE:
                case OTILDE_UC_CODE:
                case OUML_LC_CODE:
                case OUML_UC_CODE:
                case UGRAVE_LC_CODE:
                case UGRAVE_UC_CODE:
                case UACUTE_LC_CODE:
                case UACUTE_UC_CODE:
                case UCIRC_LC_CODE:
                case UCIRC_UC_CODE:
                case UUML_LC_CODE:
                case UUML_UC_CODE:
                    return valorConv;
                default:
                    return 0;
            }
        }
   }
    return 0;
}



int Rpi2040UartKeyboard::getSpecialCodes2(uint8_t arr[], int length)
{
    //Starts with ESC[
    if ((length > 2) && arr[0] == (uint8_t)RECV_SPECIAL_2_CODE)
    {
        if((length >= 3)) {
            char values[32];
            int vcount = 0;
            for (int i=2; i < length; i++)
            {
                values[vcount] = (char)arr[i];
                vcount++;
            }
            int valorConv = atoi(values);

            switch(valorConv)
            {
                case _1RST_CODE:
                case _2ND_CODE:
                case _3RD_CODE:
                case EURO_CODE:
                case PARA_CODE:
                case DOTA_CODE:
                case GRAU_CODE:
                    return valorConv;
                default:
                    return 0;
            }
        }
   }
    return 0;
}


int Rpi2040UartKeyboard::getNormalCode(uint8_t arr[], int length)
{
    if (length > 0)
    {
        return (int)arr[0];
    }
   return 0;
}


Rpi2040UartKeyboard& Rpi2040UartKeyboard::getInstance()
{
    if (Rpi2040UartKeyboard::_me == 0)
    {
        Rpi2040UartKeyboard::_me = new Rpi2040UartKeyboard();
    }
    return (*Rpi2040UartKeyboard::_me);
}


void Rpi2040UartKeyboard::onUartRXEvent()
{
    char ola[32];
    uint8_t ichar = 0;
    int readCode = 0;
    int bufferSize = 0;
    bool charRecognized = false;


    if (Rpi2040UartKeyboard::getInstance().isInterruptLoop()) {
        //uart_puts(Rpi2040Uart::getInstance().getUart(), "loop interrompido!");
        return;
    }


    while (uart_is_readable_within_us(Rpi2040Uart::getInstance().getUart(), 200)) {

        ichar = uart_getc(Rpi2040Uart::getInstance().getUart());

        if (ichar > 0) {
            Rpi2040UartKeyboard::_uartBuffer[Rpi2040UartKeyboard::_uartBufferCounter] = ichar;

            Rpi2040UartKeyboard::_uartBufferCounter ++;
            if (Rpi2040UartKeyboard::_uartBufferCounter > 9) Rpi2040UartKeyboard::_uartBufferCounter = 0;
        }

        if (uart_is_writable(Rpi2040Uart::getInstance().getUart())) {
            uart_putc(Rpi2040Uart::getInstance().getUart(),'#');
        }

        busy_wait_ms(50);
    }

    if ((Rpi2040UartKeyboard::_uartBufferCounter > 0) && uart_is_writable(Rpi2040Uart::getInstance().getUart()) && (ichar != 0)) {


        //bufferSize =  (sizeof(Rpi2040UartKeyboard::_uartBuffer) / sizeof(Rpi2040UartKeyboard::_uartBuffer[0]));
        bufferSize = Rpi2040UartKeyboard::_uartBufferCounter;


        readCode = Rpi2040UartKeyboard::getInstance().getESCFnCodes(Rpi2040UartKeyboard::_uartBuffer,bufferSize);
        if (readCode > 0) {
             KeyboardMessage::getInstance()._rawCode =  '\0';
             KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UartKeyboard::getInstance().parseRawKeycode(WKTYPE_FN,readCode);

             charRecognized = true;
        }

        if (!charRecognized) {
            readCode = Rpi2040UartKeyboard::getInstance().getESCArrowCodes(Rpi2040UartKeyboard::_uartBuffer,bufferSize);
            if (readCode > 0) {
                 KeyboardMessage::getInstance()._rawCode =  '\0';
                 KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UartKeyboard::getInstance().parseRawKeycode(WKTYPE_ARROWS,readCode);

                 charRecognized = true;
            }
        }

        if (!charRecognized) {
            readCode = Rpi2040UartKeyboard::getInstance().getSpecialCodes2(Rpi2040UartKeyboard::_uartBuffer,bufferSize);
            if (readCode > 0) {
                 KeyboardMessage::getInstance()._rawCode =  '\0';
                 KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UartKeyboard::getInstance().parseRawKeycode(WKTYPE_SPECIAL_2,readCode);

                 charRecognized = true;
            }
        }

        if (!charRecognized) {
            readCode = Rpi2040UartKeyboard::getInstance().getESCExtraCodes(Rpi2040UartKeyboard::_uartBuffer,bufferSize);

            if (readCode > 0) {
                 KeyboardMessage::getInstance()._rawCode =  '\0';
                 KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UartKeyboard::getInstance().parseRawKeycode(WKTYPE_EXTRA,readCode);

                 charRecognized = true;
            }
        }


        if (!charRecognized) {
            //uart_puts(Rpi2040Uart::getInstance().getUart(), "passo 4");

            readCode = Rpi2040UartKeyboard::getInstance().getNormalCode(Rpi2040UartKeyboard::_uartBuffer,bufferSize);
            if (readCode > 0) {
                //uart_puts(Rpi2040Uart::getInstance().getUart(), "passo 4,5");
                KeyboardMessage::getInstance()._rawCode =  (char)readCode;
                KeyboardMessage::getInstance()._keyboardKeyCode =  Rpi2040UartKeyboard::getInstance().parseRawKeycode(-1,readCode);

                charRecognized = false;
            }
        }

        /*uart_puts(Rpi2040Uart::getInstance().getUart(), "passo 5");

        uart_puts(Rpi2040Uart::getInstance().getUart(), "Caractere recebido: [");
        sprintf(ola, "] - Mem [%lu], Código: [%d]", (unsigned long)AppGlobals::getFreeHeap(),  ichar);
        uart_puts(Rpi2040Uart::getInstance().getUart(), ola);*/
        for (int i = 0; i < Rpi2040UartKeyboard::_uartBufferCounter; i++)
        {
            /*sprintf(ola, "{%d}(%c)", Rpi2040UartKeyboard::_uartBuffer[i], (char)Rpi2040UartKeyboard::_uartBuffer[i]);
            uart_puts(Rpi2040Uart::getInstance().getUart(), ola);*/
            Rpi2040UartKeyboard::_uartBuffer[i]=0;
        }

        Rpi2040UartKeyboard::_uartBufferCounter = 0;
        KeyboardMessage::getInstance()._sharedInterruptedLoop = true;

    }

}

void Rpi2040UartKeyboard::setup()
{

    int bufferSize =  (sizeof(Rpi2040UartKeyboard::_uartBuffer) / sizeof(Rpi2040UartKeyboard::_uartBuffer[0]));

    for (int i = 0; i < bufferSize; i++){
        Rpi2040UartKeyboard::_uartBuffer[i]=0;
    }
    Rpi2040UartKeyboard::_uartBufferCounter = 0;

    Rpi2040Uart::getInstance().defineRXIRQ(Rpi2040UartKeyboard::onUartRXEvent);

    KeyboardMessage::getInstance()._rawCode='\0';
    KeyboardMessage::getInstance()._sharedInterruptedLoop=false;
    KeyboardMessage::getInstance()._keyboardKeyCode=-1;

}

void Rpi2040UartKeyboard::setInterruptLoop(bool interruptLoop)
{
    /* Unfortunately, the IRQ Handler lost the callback info, so I have to
        use a 3rd class to handle it in other location of memory, bizarre! */
    KeyboardMessage::getInstance()._sharedInterruptedLoop = interruptLoop;

}

bool Rpi2040UartKeyboard::isInterruptLoop() const
{
    /* Unfortunately, the IRQ Handler lost the callback info, so I have to
        use a 3rd class to handle it in other location of memory, bizarre! */
    return (KeyboardMessage::getInstance()._sharedInterruptedLoop);
}


KeyboardEngine & Rpi2040UartKeyboard:: setCallback(KeyboardCallback *keyboardCallback)
{
    /* Unfortunately, the IRQ Handler lost the callback info, so I have to
        use a 3rd class to handle it in other location of memory, bizarre! */
    KeyboardMessage::getInstance()._sharedCallback = keyboardCallback;


    return (*this);
}

KeyboardEngine & Rpi2040UartKeyboard::pressKey(const int keyCode, const char rawChar)
{
    if (KeyboardMessage::getInstance()._sharedCallback == 0)
    {
        return (*this);
    }

    //cout << "Key Pressed: keyboard_engine_code = [" << keyCode << "] rawchar=[" << rawChar << "]" << endl;
    setInterruptLoop((*KeyboardMessage::getInstance()._sharedCallback).execute(keyCode, rawChar));

    return (*this);
}


int Rpi2040UartKeyboard::parseRawKeycode(int rawKeyType, int rawKeyCode)
{
    if (rawKeyType == WKTYPE_FN)
    {
        cout <<"Tipo fn" << rawKeyCode << endl;
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
            return KeyboardEngine::KEY_SPACE;
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
    } else if (rawKeyType == WKTYPE_SPECIAL_1){
        switch (rawKeyCode)
        {
            case CEDILLA_UC_CODE: return KeyboardEngine::KEY_CEDILLA_LC_CODE;
            case CEDILLA_LC_CODE: return KeyboardEngine::KEY_CEDILLA_UC_CODE;
            case ATILDE_LC_CODE: return KeyboardEngine::KEY_ATILDE_LC_CODE;
            case ATILDE_UC_CODE: return KeyboardEngine::KEY_ATILDE_UC_CODE;
            case AGRAVE_LC_CODE: return KeyboardEngine::KEY_AGRAVE_LC_CODE;
            case AGRAVE_UC_CODE: return KeyboardEngine::KEY_AGRAVE_UC_CODE;
            case AACUTE_LC_CODE: return KeyboardEngine::KEY_AACUTE_LC_CODE;
            case AACUTE_UC_CODE: return KeyboardEngine::KEY_AACUTE_UC_CODE;
            case ACIRC_LC_CODE: return KeyboardEngine::KEY_ACIRC_LC_CODE;
            case ACIRC_UC_CODE: return KeyboardEngine::KEY_ACIRC_UC_CODE;
            case AUML_LC_CODE: return KeyboardEngine::KEY_AUML_LC_CODE;
            case AUML_UC_CODE: return KeyboardEngine::KEY_AUML_UC_CODE;
            case ARING_LC_CODE: return KeyboardEngine::KEY_ARING_LC_CODE;
            case ARING_UC_CODE: return KeyboardEngine::KEY_ARING_UC_CODE;
            case EGRAVE_LC_CODE: return KeyboardEngine::KEY_EGRAVE_LC_CODE;
            case EGRAVE_UC_CODE: return KeyboardEngine::KEY_EGRAVE_UC_CODE;
            case EACUTE_LC_CODE: return KeyboardEngine::KEY_EACUTE_LC_CODE;
            case EACUTE_UC_CODE: return KeyboardEngine::KEY_EACUTE_UC_CODE;
            case ECIRC_LC_CODE: return KeyboardEngine::KEY_ECIRC_LC_CODE;
            case ECIRC_UC_CODE: return KeyboardEngine::KEY_ECIRC_UC_CODE;
            case EUML_LC_CODE: return KeyboardEngine::KEY_EUML_LC_CODE;
            case EUML_UC_CODE: return KeyboardEngine::KEY_EUML_UC_CODE;
            case IGRAVE_LC_CODE: return KeyboardEngine::KEY_IGRAVE_LC_CODE;
            case IGRAVE_UC_CODE: return KeyboardEngine::KEY_IGRAVE_UC_CODE;
            case IACUTE_LC_CODE: return KeyboardEngine::KEY_IACUTE_LC_CODE;
            case IACUTE_UC_CODE: return KeyboardEngine::KEY_IACUTE_UC_CODE;
            case ICIRC_LC_CODE: return KeyboardEngine::KEY_ICIRC_LC_CODE;
            case ICIRC_UC_CODE: return KeyboardEngine::KEY_ICIRC_UC_CODE;
            case IUML_LC_CODE: return KeyboardEngine::KEY_IUML_LC_CODE;
            case IUML_UC_CODE: return KeyboardEngine::KEY_IUML_UC_CODE;
            case NTILDE_LC_CODE: return KeyboardEngine::KEY_NTILDE_LC_CODE;
            case NTILDE_UC_CODE: return KeyboardEngine::KEY_NTILDE_UC_CODE;
            case OGRAVE_LC_CODE: return KeyboardEngine::KEY_OGRAVE_LC_CODE;
            case OGRAVE_UC_CODE: return KeyboardEngine::KEY_OGRAVE_UC_CODE;
            case OACUTE_LC_CODE: return KeyboardEngine::KEY_OACUTE_LC_CODE;
            case OACUTE_UC_CODE: return KeyboardEngine::KEY_OACUTE_UC_CODE;
            case OCIRC_LC_CODE: return KeyboardEngine::KEY_OCIRC_LC_CODE;
            case OCIRC_UC_CODE: return KeyboardEngine::KEY_OCIRC_UC_CODE;
            case OTILDE_LC_CODE: return KeyboardEngine::KEY_OTILDE_LC_CODE;
            case OTILDE_UC_CODE: return KeyboardEngine::KEY_OTILDE_UC_CODE;
            case OUML_LC_CODE: return KeyboardEngine::KEY_OUML_LC_CODE;
            case OUML_UC_CODE: return KeyboardEngine::KEY_OUML_UC_CODE;
            case UGRAVE_LC_CODE: return KeyboardEngine::KEY_UGRAVE_LC_CODE;
            case UGRAVE_UC_CODE: return KeyboardEngine::KEY_UGRAVE_UC_CODE;
            case UACUTE_LC_CODE: return KeyboardEngine::KEY_UACUTE_LC_CODE;
            case UACUTE_UC_CODE: return KeyboardEngine::KEY_UACUTE_UC_CODE;
            case UCIRC_LC_CODE: return KeyboardEngine::KEY_UCIRC_LC_CODE;
            case UCIRC_UC_CODE: return KeyboardEngine::KEY_UCIRC_UC_CODE;
            case UUML_LC_CODE: return KeyboardEngine::KEY_UUML_LC_CODE;
            case UUML_UC_CODE: return KeyboardEngine::KEY_UUML_UC_CODE;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    } else if (rawKeyType == WKTYPE_SPECIAL_2){
        switch (rawKeyCode)
        {

            case _1RST_CODE: return KeyboardEngine::KEY_1RST_CODE;
            case _2ND_CODE: return KeyboardEngine::KEY_2ND_CODE;
            case _3RD_CODE: return KeyboardEngine::KEY_3RD_CODE;
            case EURO_CODE: return KeyboardEngine::KEY_EURO_CODE;
            case PARA_CODE: return KeyboardEngine::KEY_PARA_CODE;
            case DOTA_CODE: return KeyboardEngine::KEY_DOTA_CODE;
            case GRAU_CODE: return KeyboardEngine::KEY_GRAU_CODE;
            default:
                return KeyboardEngine::KEY_ANY;

        }
    } else {
        switch(rawKeyCode)
        {
            case RECV_ESC_CODE: return KeyboardEngine::KEY_ESCAPE;
            case RECV_ENTER: return KeyboardEngine::KEY_ENTER;
            case RECV_BACKSPACE: return KeyboardEngine::KEY_BACKSPACE;
            case RECV_TAB: return KeyboardEngine::KEY_TAB;
            case RECV_SPACE: return KeyboardEngine::KEY_SPACE;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    }
}


void Rpi2040UartKeyboard::loop()
{

    while (!isInterruptLoop()) {

        while (!isInterruptLoop())
        {
            tight_loop_contents();
        }

        //The callback function will decide if loop stops or not! Look KeyboardMessage
        pressKey(KeyboardMessage::getInstance()._keyboardKeyCode,
            KeyboardMessage::getInstance()._rawCode);

    }

    Rpi2040Uart::getInstance().disableRXIRQ();
}


void  Rpi2040UartKeyboard::destroy()
{
    Rpi2040Uart::getInstance().disableRXIRQ();
}


void Rpi2040UartKeyboard::toString()
{
    cout << "[Rpi2040UartKeyboard] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
        << endl;
}

int Rpi2040UartKeyboard::getMemSize()
{
    return sizeof((*this));
}

Rpi2040UartKeyboard::~Rpi2040UartKeyboard()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040UartKeyboard] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040UartKeyboard::Rpi2040UartKeyboard():
KeyboardEngine()
{

}



