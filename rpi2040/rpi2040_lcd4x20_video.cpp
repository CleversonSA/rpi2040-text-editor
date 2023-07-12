
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

#include <cstdio>
using std::sprintf;

//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "../engine/video_engine.hpp"
#include "../app_globals.hpp"
#include "rpi2040_lcd4x20_video.hpp"

#include "core/text_render_engine.hpp"
#include "../rpi2040_sdk/lcd_1602_i2c.c"

VideoEngine & Rpi2040Lcd4x20Video::reset()
{
    i2c_deinit(i2c_default);

#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 400000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));


    lcd_init();
    sleep_ms(100);
    lcd_clear();
    sleep_ms(100);
    lcd_init();
    sleep_ms(100);
    lcd_clear();
    sleep_ms(100);
    lcd_clear();
    sleep_ms(100);
    lcd_set_cursor(0,0);
    sleep_ms(100);
    lcd_string(" Processing...");
    sleep_ms(100);
#endif

    return (*this);
}

VideoEngine & Rpi2040Lcd4x20Video::display(int context)
{
    char * screenLine = 0;
    int totalMovs = 0;

    lcd_clear();
    lcd_set_cursor(0,0);
    lcd_char(' ');

    for (int i=0; i < (*getFrameBuffer()).getMaxRows(); i++)
    {
        lcd_set_cursor(i, 0);

        screenLine = (*getFrameBuffer()).getScreenRow(i);

        totalMovs = 0;

        for (int j=0; j < (*getFrameBuffer()).getMaxCols(); j++)
        {

            if ((*screenLine) == '\0')
            {
                lcd_char(' ');
            } else {
                lcd_char(*screenLine);
            }
            screenLine++;
            totalMovs++;

        }


        for (int j=0; j < totalMovs; j++)
        {
            screenLine--;
        }
        delete screenLine;

    }

    return (*this);
}

void Rpi2040Lcd4x20Video::toString()
{
    cout << "[Rpi2040UartVideo] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Rpi2040Lcd4x20Video::getMemSize()
{
    return sizeof((*this));
}


Rpi2040Lcd4x20Video::~Rpi2040Lcd4x20Video()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040Lcd4x20Video] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040Lcd4x20Video::Rpi2040Lcd4x20Video():
VideoEngine()
{
    reset();
}




