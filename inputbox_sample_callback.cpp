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

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "inputbox_sample_callback.hpp"
#include "widget_engine.hpp"
#include "inputbox_engine.hpp"


//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "vt100_utils.hpp"
#include "rpi2040_uart.hpp"

void InputboxSampleCallback::execute(WidgetEngine * widgetEngine)
{
    Rpi2040Uart rpi2040uart = Rpi2040Uart::getInstance();

    if ((*widgetEngine).getResultIntValue() == InputBoxEngine::OK_TRIGGERED )
    {
        uart_puts(rpi2040uart.getUart(), "Entrada: ");
        uart_puts(rpi2040uart.getUart(), (*widgetEngine).getResultCharValue1());
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());

    } else if((*widgetEngine).getResultIntValue() == InputBoxEngine::CANCEL_TRIGGERED ) {

        uart_puts(rpi2040uart.getUart(), "ENTRADA CANCELADA PELO USUARIO");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());

    } else {

        uart_puts(rpi2040uart.getUart(), "SEI LA QUE ESTADO E ESSE!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());

    }

}


void InputboxSampleCallback::toString()
{
    cout << "[InputboxSampleCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int InputboxSampleCallback::getMemSize()
{
    return sizeof((*this));
}

InputboxSampleCallback::~InputboxSampleCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[InputboxSampleCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

InputboxSampleCallback::InputboxSampleCallback():
WidgetCallback()
{

}




