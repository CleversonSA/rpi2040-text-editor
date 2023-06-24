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
#include "textengine_keyboard_callback.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/text_engine.hpp"
#include "../document/document.hpp"

void TextEngineKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * TextEngineKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void TextEngineKeyboardCallback::setTextEngine(TextEngine * textEngine)
{

    _textEngine = textEngine;

}

TextEngine * TextEngineKeyboardCallback::getTextEngine()
{

    return _textEngine;

}


bool TextEngineKeyboardCallback::execute(const int keyboardCode, const char rawChar)
{

    Document *doc = (*getTextEngine()).getDocument();

    switch(keyboardCode)
    {
        case KeyboardEngine::KEY_ANY:
            (*doc).type(rawChar);
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UP:
            (*doc).cursorMoveUp();
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_LEFT:
            (*doc).cursorMoveLeft();
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_RIGHT:
            (*doc).cursorMoveRight();
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_DOWN:
            (*doc).cursorMoveDown();
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ENTER:
            (*doc).addNewLine();
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_BACKSPACE:
        case KeyboardEngine::KEY_DEL:
            (*doc).triggerBackspace();
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_SPACE:
            (*doc).type(' ');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        default:
            break;
    }

    return false;

}

void TextEngineKeyboardCallback::toString()
{
    cout << "[TextEngineKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextEngineKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

TextEngineKeyboardCallback::~TextEngineKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextEngineKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextEngineKeyboardCallback::TextEngineKeyboardCallback():
KeyboardCallback()
{

}




