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

#include "../app_globals.hpp"
#include "../csa_object.hpp"
#include "menu_keyboard_callback.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/menu_engine.hpp"

void MenuKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * MenuKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void MenuKeyboardCallback::setMenuEngine(MenuEngine * menuEngine)
{

    _menuEngine = menuEngine;

}

MenuEngine * MenuKeyboardCallback::getMenuEngine()
{

    return _menuEngine;

}


bool MenuKeyboardCallback::execute(const int keyboardCode, const char rawChar)
{

    switch(keyboardCode)
    {
        case KeyboardEngine::KEY_UP:
        case KeyboardEngine::KEY_LEFT:
            (*getMenuEngine()).cursorMoveUp();
            (*getMenuEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_RIGHT:
        case KeyboardEngine::KEY_DOWN:
            (*getMenuEngine()).cursorMoveDown();
            (*getMenuEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ENTER:
            (*getMenuEngine()).selectItem();
            return true;
            break;
        case KeyboardEngine::KEY_ESCAPE:
            (*getMenuEngine()).selectBackItem();
            return true;
        default:
            break;
    }

    return false;

}

void MenuKeyboardCallback::toString()
{
    cout << "[MenuKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int MenuKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

MenuKeyboardCallback::~MenuKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MenuKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MenuKeyboardCallback::MenuKeyboardCallback():
KeyboardCallback()
{

}




