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
#include "textview_keyboard_callback.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/textview_engine.hpp"

void TextViewKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * TextViewKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void TextViewKeyboardCallback::setTextViewEngine(TextViewEngine * textViewEngine)
{

    _textViewEngine = textViewEngine;

}

TextViewEngine * TextViewKeyboardCallback::getTextViewEngine()
{

    return _textViewEngine;

}


bool TextViewKeyboardCallback::execute(const int keyboardCode, const char rawChar)
{

    switch(keyboardCode)
    {
        case KeyboardEngine::KEY_UP:
        case KeyboardEngine::KEY_LEFT:
            (*getTextViewEngine()).cursorMoveUp();
            (*getTextViewEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_RIGHT:
        case KeyboardEngine::KEY_DOWN:
            (*getTextViewEngine()).cursorMoveDown();
            (*getTextViewEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ENTER:
        case KeyboardEngine::KEY_ESCAPE:
            (*getTextViewEngine()).closeView();
            return true;
            break;
        default:
            break;
    }

    return false;

}

void TextViewKeyboardCallback::toString()
{
    cout << "[TextViewKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextViewKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

TextViewKeyboardCallback::~TextViewKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextViewKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextViewKeyboardCallback::TextViewKeyboardCallback():
KeyboardCallback()
{

}





