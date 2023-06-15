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
#define MENU_ITEMS_PAGE_SIZE 3

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cstring>
using std::strlen;
using std::strcpy;

#include "lcd4x20_menu.hpp"
#include "menu_engine.hpp"
#include "app_globals.hpp"
#include "framebuffer.hpp"

void LCD4X20Menu::fitString(const char * text, const int max_size, int offset)
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

MenuEngine & LCD4X20Menu::render()
{
    FrameBuffer *fb = getFrameBuffer();
    int menuItemLine = 1;
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


    for (int i =0; i<getMenuItemCount(); i++)
    {
        if (getMenuItemPos() >= i) {
            lastPage = false;
        } else {
            lastPage = true;
        }

        if ((i>0) && ((i % MENU_ITEMS_PAGE_SIZE ) == 0) && !lastPage) {
           (*fb)
                .clearScreen()
                .cursorMoveBegin()
                .write({"+-|              |-+"}, 20)
                .write({"|                  |"}, 20)
                .write({"|                  |"}, 20)
                .write({"|                  |"}, 20)
                .gotoXY(0,3);
            fitString(getTitle(), 14);
            menuItemLine = 1;
        } else if ((i>0) && ((i % MENU_ITEMS_PAGE_SIZE ) == 0) && lastPage){
            break;
        }

        if (i == getMenuItemPos()) {
           (*fb)
                .gotoXY(menuItemLine, 0)
                .write({">"},1);
        } else {
           (*fb)
                .gotoXY(menuItemLine, 1);
        }

        fitString(getMenuItemLabel(i),18,0);

        if (i == getMenuItemPos()) {
           (*fb)
                .gotoXY(menuItemLine, 20)
                .write({"<"},1);
        }
        menuItemLine++;
    }

    return (*this);
}

void LCD4X20Menu::setFrameBuffer(FrameBuffer * framebuffer)
{
    _framebuffer = framebuffer;
}

FrameBuffer * LCD4X20Menu::getFrameBuffer() const
{
    return (_framebuffer);
}

void LCD4X20Menu::toString()
{
    cout << "[LCD4X20Splashbox] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LCD4X20Menu::getMemSize()
{
    return sizeof((*this));
}


LCD4X20Menu::~LCD4X20Menu()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LCD4X20Menu] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LCD4X20Menu::LCD4X20Menu(FrameBuffer * framebuffer):
MenuEngine(),
_framebuffer(framebuffer)
{

}


