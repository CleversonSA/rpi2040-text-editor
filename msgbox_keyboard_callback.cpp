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

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "msgbox_keyboard_callback.hpp"
#include "keyboard_engine.hpp"
#include "msgbox_engine.hpp"

void MsgboxKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * MsgboxKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void MsgboxKeyboardCallback::setMsgboxEngine(MsgBoxEngine * msgboxEngine)
{

    _msgboxEngine = msgboxEngine;

}

MsgBoxEngine * MsgboxKeyboardCallback::getMsgBoxEngine()
{

    return _msgboxEngine;

}


bool MsgboxKeyboardCallback::execute(const int keyboardCode, const char rawChar)
{

    switch(keyboardCode)
    {
        case KeyboardEngine::KEY_UP:
        case KeyboardEngine::KEY_LEFT:
            (*getMsgBoxEngine()).cursorMovePreviousButton();
            (*getMsgBoxEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_RIGHT:
        case KeyboardEngine::KEY_DOWN:
            (*getMsgBoxEngine()).cursorMoveNextButton();
            (*getMsgBoxEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ENTER:
            (*getMsgBoxEngine()).selectButton();
            return true;
            break;
        default:
            break;
    }

    return false;

}

void MsgboxKeyboardCallback::toString()
{
    cout << "[MsgboxKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int MsgboxKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

MsgboxKeyboardCallback::~MsgboxKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MsgboxKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MsgboxKeyboardCallback::MsgboxKeyboardCallback():
KeyboardCallback()
{

}



