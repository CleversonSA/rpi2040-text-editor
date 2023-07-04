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
#include "../engine/text_render_engine.hpp"
#include "../document/document.hpp"

void TextEngineKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * TextEngineKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void TextEngineKeyboardCallback::setTextEngine(TextRenderEngine * textEngine)
{

    _textEngine = textEngine;

}

TextRenderEngine * TextEngineKeyboardCallback::getTextEngine()
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
        case KeyboardEngine::KEY_ATILDE_UC_CODE:
            (*doc).type('~').type('A');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_TILDE:
            (*doc).type('~');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ATILDE_LC_CODE:
            (*doc).type('~').type('a');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_NTILDE_LC_CODE:
            (*doc).type('~').type('n');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_NTILDE_UC_CODE:
            (*doc).type('~').type('N');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OTILDE_LC_CODE:
            (*doc).type('~').type('o');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OTILDE_UC_CODE:
            (*doc).type('~').type('O');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ACUTE:
            (*doc).type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_AGRAVE:
            (*doc).type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ACIRC:
            (*doc).type('^');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_AUML:
            (*doc).type('o');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_AACUTE_UC_CODE:
            (*doc).type('A').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_AACUTE_LC_CODE:
            (*doc).type('a').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_EACUTE_UC_CODE:
            (*doc).type('E').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_EACUTE_LC_CODE:
            (*doc).type('e').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_IACUTE_LC_CODE:
            (*doc).type('i').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_IACUTE_UC_CODE:
            (*doc).type('I').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OACUTE_UC_CODE:
            (*doc).type('O').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OACUTE_LC_CODE:
            (*doc).type('o').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UACUTE_UC_CODE:
            (*doc).type('U').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UACUTE_LC_CODE:
            (*doc).type('u').type('\'');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_CEDILLA_LC_CODE:
            (*doc).type('c');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_CEDILLA_UC_CODE:
            (*doc).type('C');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_AGRAVE_UC_CODE:
            (*doc).type('\'').type('A');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_AGRAVE_LC_CODE:
            (*doc).type('\'').type('a');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_EGRAVE_UC_CODE:
            (*doc).type('\'').type('E');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_EGRAVE_LC_CODE:
            (*doc).type('\'').type('e');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_IGRAVE_UC_CODE:
            (*doc).type('\'').type('I');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_IGRAVE_LC_CODE:
            (*doc).type('\'').type('i');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OGRAVE_UC_CODE:
            (*doc).type('\'').type('O');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OGRAVE_LC_CODE:
            (*doc).type('\'').type('o');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UGRAVE_UC_CODE:
            (*doc).type('\'').type('U');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UGRAVE_LC_CODE:
            (*doc).type('\'').type('u');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ACIRC_UC_CODE:
            (*doc).type('o').type('A');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ACIRC_LC_CODE:
            (*doc).type('o').type('a');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ECIRC_UC_CODE:
            (*doc).type('o').type('E');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ECIRC_LC_CODE:
            (*doc).type('o').type('E');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ICIRC_UC_CODE:
            (*doc).type('o').type('I');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_ICIRC_LC_CODE:
            (*doc).type('o').type('i');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OCIRC_UC_CODE:
            (*doc).type('o').type('A');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_OCIRC_LC_CODE:
            (*doc).type('o').type('o');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UCIRC_UC_CODE:
            (*doc).type('o').type('U');
            (*getTextEngine()).render();
            (*getVideoEngine()).display();
            break;
        case KeyboardEngine::KEY_UCIRC_LC_CODE:
            (*doc).type('o').type(' ');
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




