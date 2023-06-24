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
#define LINE_ITEMS_PAGE_SIZE 3

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cstring>
using std::strlen;
using std::strcpy;

#include "lcd4x20_textview.hpp"
#include "../engine/textview_engine.hpp"
#include "../engine/menu_engine.hpp"
#include "../app_globals.hpp"
#include "../video/framebuffer.hpp"

void LCD4X20TextView::fitString(const char * text, const int max_size, int offset)
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

TextViewEngine & LCD4X20TextView::render()
{
    FrameBuffer *fb = getFrameBuffer();
    int textLine = 1;
    bool lastPage = false;

    (*fb)
        .clearScreen()
        .cursorMoveBegin()
        .write({"+-|              |-+"}, 20)
        .write({"|                  |"}, 20)
        .write({"|                  |"}, 20)
        .write({"|                  |"}, 20)
        .cursorMoveBegin()
        .gotoXY(0,3);

    fitString(getTitle(), 14);


    for (int i =0; i<getViewLinesCount(); i++)
    {
        if (getViewLinePos() >= i) {
            lastPage = false;
        } else {
            lastPage = true;
        }

        if ((i>0) && ((i % LINE_ITEMS_PAGE_SIZE ) == 0) && !lastPage) {
           (*fb)
                .clearScreen()
                .cursorMoveBegin()
                .write({"+-|              |-+"}, 20)
                .write({"|                  |"}, 20)
                .write({"|                  |"}, 20)
                .write({"|                  |"}, 20)
                .gotoXY(0,3);
            fitString(getTitle(), 14);
            textLine = 1;
        } else if ((i>0) && ((i % LINE_ITEMS_PAGE_SIZE ) == 0) && lastPage){
            break;
        }

        if (i == getViewLinePos()) {
           (*fb)
                .gotoXY(textLine, 0)
                .write({">"},1);
        } else {
           (*fb)
                .gotoXY(textLine, 1);
        }

        fitString(getTextLine(i),18,0);

        if (i == getViewLinePos()) {
           (*fb)
                .gotoXY(textLine, 20)
                .write({"<"},1);
        }
        textLine++;
    }

    return (*this);
}

void LCD4X20TextView::setFrameBuffer(FrameBuffer * framebuffer)
{
    _framebuffer = framebuffer;
}

FrameBuffer * LCD4X20TextView::getFrameBuffer() const
{
    return (_framebuffer);
}

void LCD4X20TextView::toString()
{
    cout << "[LCD4X20TextView] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LCD4X20TextView::getMemSize()
{
    return sizeof((*this));
}


LCD4X20TextView::~LCD4X20TextView()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LCD4X20TextView] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LCD4X20TextView::LCD4X20TextView(FrameBuffer * framebuffer, MenuEngine * menuEngineInstance):
TextViewEngine(menuEngineInstance),
_framebuffer(framebuffer)
{

}



