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
#include "inputbox_keyboard_callback.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/inputbox_engine.hpp"

void InputboxKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * InputboxKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void InputboxKeyboardCallback::setInputboxEngine(InputBoxEngine * inputboxEngine)
{

    _inputboxEngine = inputboxEngine;

}

InputBoxEngine * InputboxKeyboardCallback::getInputboxEngine()
{

    return _inputboxEngine;

}


bool InputboxKeyboardCallback::execute(const int keyboardCode, const char rawChar)
{

    switch(keyboardCode)
    {
        case KeyboardEngine::KEY_ANY:
            (*getInputboxEngine()).type(rawChar);
            (*getInputboxEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_SPACE:
            (*getInputboxEngine()).type('\b');
            (*getInputboxEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_DEL:
            (*getInputboxEngine()).clearInput();
            (*getInputboxEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_BACKSPACE:
            (*getInputboxEngine()).triggerBackspace();
            (*getInputboxEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ENTER:
            (*getInputboxEngine()).triggerEnter();
            (*getInputboxEngine()).render();
            return true;
            break;
        case KeyboardEngine::KEY_ESCAPE:
            (*getInputboxEngine()).triggerESC();
            (*getInputboxEngine()).render();
            return true;
            break;
        default:
            break;
    }

    return false;

}

void InputboxKeyboardCallback::toString()
{
    cout << "[InputboxKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int InputboxKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

InputboxKeyboardCallback::~InputboxKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[InputboxKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

InputboxKeyboardCallback::InputboxKeyboardCallback():
KeyboardCallback()
{

}





