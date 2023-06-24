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

#include "../engine/text_engine.hpp"
#include "rpi2040_text_engine.hpp"

//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"


void Rpi2040TextEngine::renderColRow(int row, int col, int bytes)
{
    TextEngine::renderColRow(row, col, bytes);

    if(_ledOn == 1)
    {
        _ledOn = 0;
    } else {
        _ledOn = 1;
    }
    gpio_put(LED_PIN, _ledOn);
}


void Rpi2040TextEngine::toString()
{
    cout << "[Rpi2040TextEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Rpi2040TextEngine::getMemSize()
{
    return sizeof((*this));
}

Rpi2040TextEngine::~Rpi2040TextEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040TextEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040TextEngine::Rpi2040TextEngine(Document * document, VideoEngine *videoEngine):
TextEngine(document, videoEngine),
_ledOn(1)
{
    #ifndef PICO_DEFAULT_LED_PIN
        #warning blink example requires a board with a regular LED
    #else
        LED_PIN = PICO_DEFAULT_LED_PIN;
        gpio_init(LED_PIN);
        gpio_set_dir(LED_PIN, GPIO_OUT);
    #endif

}




