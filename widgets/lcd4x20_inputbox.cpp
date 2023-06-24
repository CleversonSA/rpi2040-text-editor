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
using std::strcpy;

#include "lcd4x20_inputbox.hpp"
#include "../engine/inputbox_engine.hpp"
#include "../app_globals.hpp"
#include "../video/framebuffer.hpp"

void LCD4X20InputBox::fitString(const char * text, const int max_size, int offset, bool padding)
{
    FrameBuffer *fb = getFrameBuffer();

    int textLen = strlen(text) - offset;
    if(textLen < max_size)
    {
        for (int i=0; i<textLen; i++) {
            if (text[i+offset] == '\0')
            {
                break;
            }
            (*fb)
                .write(text[i+offset]);
        }
        if (padding == true)
        {
            for (int i = textLen; i<max_size; i++) {
                (*fb)
                    .write(' ');
            }
        }
    } else {
        for (int i=0; i<max_size; i++) {
            if (text[i+offset] == '\0')
            {
                break;
            }
            (*fb)
                .write(text[i+offset]);
        }
    }
}

InputBoxEngine & LCD4X20InputBox::render()
{
    FrameBuffer *fb = getFrameBuffer();

    (*fb)
        .clearScreen()
        .cursorMoveBegin()
        .write({"+-|              |-+"}, 20)
        .write({"|                  |"}, 20)
        .write({">                  <"}, 20)
        .write({"+------------------+"}, 20)
        .cursorMoveBegin()
        .gotoXY(0,3);
    fitString(getTitle(), 14);


    (*fb).gotoXY(1,1);
    fitString(getMessage(),18);

    (*fb).gotoXY(2,1);
    if(getUserInput() != 0) {
        fitString(getUserInput(),18, 0, false);
    }
    (*fb).write('_');

    return (*this);
}

void LCD4X20InputBox::setFrameBuffer(FrameBuffer * framebuffer)
{
    _framebuffer = framebuffer;
}

FrameBuffer * LCD4X20InputBox::getFrameBuffer() const
{
    return (_framebuffer);
}

void LCD4X20InputBox::toString()
{
    cout << "[LCD4X20InputBox] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LCD4X20InputBox::getMemSize()
{
    return sizeof((*this));
}


LCD4X20InputBox::~LCD4X20InputBox()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LCD4X20InputBox] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LCD4X20InputBox::LCD4X20InputBox(FrameBuffer * framebuffer):
InputBoxEngine(),
_framebuffer(framebuffer)
{
    setMaxInputSize(18);
}

