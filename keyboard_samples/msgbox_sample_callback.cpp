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
#include <iostream>
using std::cout;
using std::endl;

#include "../app_globals.hpp"
#include "../csa_object.hpp"
#include "msgbox_sample_callback.hpp"
#include "../engine/widget_engine.hpp"
#include "../engine/msgbox_engine.hpp"


//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "vt100_utils.hpp"
#include "rpi2040_uart.hpp"

void MsgboxSampleCallback::execute(WidgetEngine * widgetEngine)
{
    Rpi2040Uart rpi2040uart = Rpi2040Uart::getInstance();

    switch((*widgetEngine).getResultIntValue())
    {
    case MsgBoxEngine::BTN_YES:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O SIM");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    case MsgBoxEngine::BTN_NO:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O NAO");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    case MsgBoxEngine::BTN_CANCEL:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O CANCELAR");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
     case MsgBoxEngine::BTN_OK:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O OK");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    default:
        break;
    }

}


void MsgboxSampleCallback::toString()
{
    cout << "[MsgboxSampleCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int MsgboxSampleCallback::getMemSize()
{
    return sizeof((*this));
}

MsgboxSampleCallback::~MsgboxSampleCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MsgboxSampleCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MsgboxSampleCallback::MsgboxSampleCallback():
WidgetCallback()
{

}



