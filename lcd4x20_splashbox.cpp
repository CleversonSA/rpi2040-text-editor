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

#include "lcd4x20_splashbox.hpp"
#include "splashbox_engine.hpp"
#include "app_globals.hpp"
#include "framebuffer.hpp"

void LCD4X20Splashbox::fitString(const char * text, const int max_size, int offset)
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

SplashBoxEngine & LCD4X20Splashbox::render()
{
    FrameBuffer *fb = getFrameBuffer();

    (*fb)
        .clearScreen()
        .cursorMoveBegin();

    switch(getIconType())
    {
    case(SplashBoxEngine::QUESTION_ICON):
        (*fb)
            .write({"??|              |??"}, 20)
            .write({"?                  ?"}, 20)
            .write({"?                  ?"}, 20)
            .write({"??----------------??"}, 20);
        break;
    case(SplashBoxEngine::EXCLAMATION_ICON):
        (*fb)
            .write({"!!|              |!!"}, 20)
            .write({"!                  !"}, 20)
            .write({"!                  !"}, 20)
            .write({"!!----------------!!"}, 20);
        break;
    case(SplashBoxEngine::ERROR_ICON):
        (*fb)
            .write({"##|              |##"}, 20)
            .write({"#                  #"}, 20)
            .write({"#                  #"}, 20)
            .write({"##----------------##"}, 20);
        break;
    case(SplashBoxEngine::INFO_ICON):
        (*fb)
            .write({"ii|              |ii"}, 20)
            .write({"i                  i"}, 20)
            .write({"i                  i"}, 20)
            .write({"ii----------------ii"}, 20);
        break;
    default:
        (*fb)
            .write({"+-|              |-+"}, 20)
            .write({"|                  |"}, 20)
            .write({"|                  |"}, 20)
            .write({"+------------------+"}, 20);
        break;
    }

    (*fb)
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
    if (strlen(getMessage())>=36)
    {
        (*fb).gotoXY(3,1);
        fitString(getMessage(),18,36);
    }

    return (*this);
}

void LCD4X20Splashbox::setFrameBuffer(FrameBuffer * framebuffer)
{
    _framebuffer = framebuffer;
}

FrameBuffer * LCD4X20Splashbox::getFrameBuffer() const
{
    return (_framebuffer);
}

void LCD4X20Splashbox::toString()
{
    cout << "[LCD4X20Splashbox] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LCD4X20Splashbox::getMemSize()
{
    return sizeof((*this));
}


LCD4X20Splashbox::~LCD4X20Splashbox()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LCD4X20Splashbox] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LCD4X20Splashbox::LCD4X20Splashbox(FrameBuffer * framebuffer):
SplashBoxEngine(),
_framebuffer(framebuffer)
{

}

