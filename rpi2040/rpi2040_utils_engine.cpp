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

#include <iomanip>
using std::setw;

#include <cstring>
using std::strlen;
using std::sprintf;

#include "rpi2040_utils_engine.hpp"

//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/watchdog.h"


void Rpi2040UtilsEngine::deactivateActStatus() {
    gpio_put(AppGlobals::RPI2040_USB_IO_LED_PIN, 0);
    sleep_ms(50);
}

void Rpi2040UtilsEngine::activateActStatus() {
    gpio_put(AppGlobals::RPI2040_USB_IO_LED_PIN, 1);
    sleep_ms(50);
}


void Rpi2040UtilsEngine::softReset() {
    watchdog_enable(1, 1);
    while(1);
}

void Rpi2040UtilsEngine::sleepMs(long ms)
{
    cout << "dormindo " << ms << "secs" << endl;
    sleep_ms(ms);
}


void Rpi2040UtilsEngine::toString()
{
    cout << "[Rpi2040UtilsEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Rpi2040UtilsEngine::getMemSize()
{
    return sizeof((*this));
}

Rpi2040UtilsEngine::~Rpi2040UtilsEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040UtilsEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040UtilsEngine::Rpi2040UtilsEngine():
UtilsEngine()
{

}




