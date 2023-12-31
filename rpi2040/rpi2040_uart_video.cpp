
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

#include "rpi2040_uart_video.hpp"
#include "rpi2040_uart.hpp"
#include "../engine/video_engine.hpp"
#include "../app_globals.hpp"
#include "../utils/vt100_utils.hpp"
#include "rpi2040_uart_keyboard.hpp"

#include "core/text_render_engine.hpp"


void Rpi2040UartVideo::displayContext()
{
    char * screenLine = 0;
    int totalMovs = 0;

    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::clearScreen());
    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::gotoXY(1,1));

    for (int i=0; i < (*getFrameBuffer()).getMaxRows(); i++)
    {
        screenLine = (*getFrameBuffer()).getScreenRow(i);

        totalMovs = 0;


        uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::gotoXY(i+1,1));

        for (int j=0; j < (*getFrameBuffer()).getMaxCols(); j++)
        {

            if ((*screenLine) == '\0')
            {
                uart_putc(Rpi2040Uart::getInstance().getUart(), ' ');
            } else {
                uart_putc(Rpi2040Uart::getInstance().getUart(), (*screenLine));
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

}

void Rpi2040UartVideo::displayDocumentContext()
{
    char * screenLine = 0;
    int totalMovs = 0;
    int checksumLine = 0;

    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::gotoXY(1,1));

    // Ruler
    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::inverseAttribute());
    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::highlightAttribute());
    uart_putc(Rpi2040Uart::getInstance().getUart(), 'L');
    for (int i=1; i< (*getFrameBuffer()).getMaxCols(); i++ )
    {
        uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::gotoXY(1,i+1));
        if ((i % 5) == 0)
            uart_putc(Rpi2040Uart::getInstance().getUart(), '#');
        else
            uart_putc(Rpi2040Uart::getInstance().getUart(), '-');
    }
    uart_putc(Rpi2040Uart::getInstance().getUart(), 'R');
    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::disableAttributes());
    uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::gotoXY(2,1));


    for (int i=0; i < (*getFrameBuffer()).getMaxRows(); i++)
    {
        screenLine = (*getFrameBuffer()).getScreenRow(i);

        totalMovs = 0;
        checksumLine = (*getFrameBuffer()).calculateScreenRowChecksum(i);

        if (checksumLine != (*getFrameBuffer()).getScreenRowChecksum(i)) {

            uart_puts(Rpi2040Uart::getInstance().getUart(), VT100Utils::gotoXY(i+2,1));

            for (int j=0; j < (*getFrameBuffer()).getMaxCols(); j++)
            {
                // I noticed uart fails if I fb needs more speed on refresh and
                // not completed the last request to send data. Rpi freezes. Lets try
                // wait a little
                /*if (!uart_is_writable(Rpi2040Uart::getInstance().getUart()))
                {
                    busy_wait_us(100);
                    uart_puts(Rpi2040Uart::getInstance().getUart(), "0");
                } else {
                    uart_puts(Rpi2040Uart::getInstance().getUart(), "1");
                }*/

                if ((*screenLine) == '\0')
                {
                    uart_putc(Rpi2040Uart::getInstance().getUart(), ' ');
                } else {
                    uart_putc(Rpi2040Uart::getInstance().getUart(), (*screenLine));
                }
                screenLine++;
                totalMovs++;


            }

            (*getFrameBuffer()).updateScreenRowChecksum(i, checksumLine);
        }

        for (int j=0; j < totalMovs; j++)
        {
            screenLine--;
        }
        delete screenLine;


    }

}


VideoEngine & Rpi2040UartVideo::display(int displayContextId)
{

    switch(displayContextId) {
        case TextRenderEngine::DISPLAY_CONTEXT_ID:
            displayDocumentContext();
            break;
        default:
            displayContext();
            break;
    }

    return (*this);
}

void Rpi2040UartVideo::toString()
{
    cout << "[Rpi2040LCD4X20Video] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Rpi2040UartVideo::getMemSize()
{
    return sizeof((*this));
}


Rpi2040UartVideo::~Rpi2040UartVideo()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040LCD4X20Video] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040UartVideo::Rpi2040UartVideo():
VideoEngine()
{

}




