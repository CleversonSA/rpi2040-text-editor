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

#include <iostream>
using std::cout;
using std::endl;

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "menu_sample_callback.hpp"
#include "widget_engine.hpp"
#include "menu_engine.hpp"


//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "vt100_utils.hpp"
#include "rpi2040_uart.hpp"


void MenuSampleCallback::execute(WidgetEngine * widgetEngine)
{
    Rpi2040Uart rpi2040uart = Rpi2040Uart::getInstance();

    char str[255];
    sprintf(str, "Voce escolheu a opcao [%s] (%s)", (*widgetEngine).getResultCharValue1(), (*widgetEngine).getResultCharValue2());
    uart_puts(rpi2040uart.getUart(), str);
    uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());

}


void MenuSampleCallback::toString()
{
    cout << "[MenuSampleCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int MenuSampleCallback::getMemSize()
{
    return sizeof((*this));
}

MenuSampleCallback::~MenuSampleCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MenuSampleCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MenuSampleCallback::MenuSampleCallback():
WidgetCallback()
{

}




