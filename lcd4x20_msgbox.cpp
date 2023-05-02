

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

#include "lcd4x20_msgbox.hpp"
#include "msgbox_engine.hpp"
#include "app_globals.hpp"
#include "framebuffer.hpp"

void LCD4X20MsgBox::fitString(const char * text, const int max_size, int offset)
{

    FrameBuffer *fb = getFrameBuffer();

    int textLen = strlen(text) - offset;
    if(textLen < max_size)
    {
        for (int i=0; i<textLen; i++) {
            (*fb)
                .write(text[i+offset]);
        }
        for (int i = textLen; i<max_size; i++) {
            (*fb)
                .write(' ');
        }
    } else {
        for (int i=0; i<max_size; i++) {
            (*fb)
                .write(text[i+offset]);
        }
    }
}

MsgBoxEngine & LCD4X20MsgBox::render()
{
    FrameBuffer *fb = getFrameBuffer();

    (*fb)
        .clearScreen()
        .cursorMoveBegin()
        .write({"+-|              |-+"}, 20)
        .write({"|                  |"}, 20)
        .write({"|                  |"}, 20)
        .write({"+------------------+"}, 20)
        .cursorMoveBegin()
        .gotoXY(0,3);

    fitString(getTitle(), 14);

    (*fb).gotoXY(1,1);
    fitString(getMessage(),18);
    if (strlen(getMessage())>=18)
    {
        (*fb).gotoXY(2,1);
        fitString(getMessage(),18,18);
    }

    return (*this);
}

void LCD4X20MsgBox::setFrameBuffer(FrameBuffer * framebuffer)
{
    _framebuffer = framebuffer;
}

FrameBuffer * LCD4X20MsgBox::getFrameBuffer() const
{
    return (_framebuffer);
}

void LCD4X20MsgBox::toString()
{
    cout << "[LCD4X20MsgBox] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LCD4X20MsgBox::getMemSize()
{
    return sizeof((*this));
}


LCD4X20MsgBox::~LCD4X20MsgBox()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LCD4X20MsgBox] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LCD4X20MsgBox::LCD4X20MsgBox(FrameBuffer * framebuffer):
MsgBoxEngine(),
_framebuffer(framebuffer)
{

}

