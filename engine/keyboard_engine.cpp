
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

#include "keyboard_engine.hpp"
#include "../app_globals.hpp"
#include "../keyboard/keyboard_callback.hpp"


void KeyboardEngine::setInterruptLoop(bool interruptLoop)
{
    _interruptLoop = interruptLoop;
}

bool KeyboardEngine::isInterruptLoop() const
{
    return _interruptLoop;
}

KeyboardEngine & KeyboardEngine::setCallback(KeyboardCallback *keyboardCallback)
{
   _keyboardCallback = keyboardCallback;

    return (*this);
}

KeyboardEngine & KeyboardEngine::pressKey(const int keyCode, const char rawChar)
{

    if (_keyboardCallback == 0)
    {
        return (*this);
    }

    _interruptLoop = (*_keyboardCallback).execute(keyCode, rawChar);


    return (*this);
}


KeyboardEngine::~KeyboardEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[KeyboardEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

KeyboardEngine::KeyboardEngine():
CSAObject(),
_interruptLoop(false)
{

}


