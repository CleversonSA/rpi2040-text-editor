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
#include "text_render_engine_keyboard_callback.hpp"
#include "engine/keyboard_engine.hpp"
#include "core/text_render_engine.hpp"
#include "document.hpp"
#include "../core_collection.hpp"
#include "../resource_collection.hpp"

int TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
int TextRenderEngineKeyboardCallback::_LALT_PRESSES_COUNT = 0;


void TextRenderEngineKeyboardCallback::setVideoEngine(VideoEngine * videoEngine)
{

    _videoEngine = videoEngine;

}

VideoEngine * TextRenderEngineKeyboardCallback::getVideoEngine()
{

    return _videoEngine;

}


void TextRenderEngineKeyboardCallback::setTextEngine(TextRenderEngine * textEngine)
{

    _textEngine = textEngine;

}

TextRenderEngine * TextRenderEngineKeyboardCallback::getTextEngine()
{

    return _textEngine;

}


bool TextRenderEngineKeyboardCallback::execute(const int keyboardCode, const char rawChar)
{

    Document *doc = (*getTextEngine()).getDocument();

    switch(keyboardCode)
    {
        case KeyboardEngine::KEY_F2:

            (*CoreCollection::getInstance().getLineZoom()).run();
            break;
        case KeyboardEngine::KEY_ESCAPE:
            if (TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT == 1)
            {
                TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT =0;
                
                (*CoreCollection::getInstance().getMainMenu()).run();
            } else {
                TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT ++;
                
            }
            break;
        case KeyboardEngine::KEY_F12:
            (*getVideoEngine()).reset();
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            
            break;
        case KeyboardEngine::KEY_ANY:
            (*doc).type(rawChar);
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_UP:
            (*doc).cursorMoveUp();
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_LEFT:
            (*doc).cursorMoveLeft();
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_RIGHT:
            (*doc).cursorMoveRight();
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_DOWN:
            (*doc).cursorMoveDown();
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ENTER:
            (*doc).addNewLine();
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_BACKSPACE:
        case KeyboardEngine::KEY_DEL:
            (*doc).triggerBackspace();
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_SPACE:
            (*doc).type(' ');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ATILDE_UC_CODE:
            (*doc).type('~').type('A');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_TILDE:
            (*doc).type('~');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ATILDE_LC_CODE:
            (*doc).type('~').type('a');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_NTILDE_LC_CODE:
            (*doc).type('~').type('n');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_NTILDE_UC_CODE:
            (*doc).type('~').type('N');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OTILDE_LC_CODE:
            (*doc).type('~').type('o');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OTILDE_UC_CODE:
            (*doc).type('~').type('O');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ACUTE:
            (*doc).type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_AGRAVE:
            (*doc).type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ACIRC:
            (*doc).type('^');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_AUML:
            (*doc).type('o');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_AACUTE_UC_CODE:
            (*doc).type('A').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_AACUTE_LC_CODE:
            (*doc).type('a').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_EACUTE_UC_CODE:
            (*doc).type('E').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_EACUTE_LC_CODE:
            (*doc).type('e').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_IACUTE_LC_CODE:
            (*doc).type('i').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_IACUTE_UC_CODE:
            (*doc).type('I').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OACUTE_UC_CODE:
            (*doc).type('O').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OACUTE_LC_CODE:
            (*doc).type('o').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            


            break;
        case KeyboardEngine::KEY_UACUTE_UC_CODE:
            (*doc).type('U').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_UACUTE_LC_CODE:
            (*doc).type('u').type('\'');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_CEDILLA_LC_CODE:
            (*doc).type('c');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_CEDILLA_UC_CODE:
            (*doc).type('C');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_AGRAVE_UC_CODE:
            (*doc).type('\'').type('A');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_AGRAVE_LC_CODE:
            (*doc).type('\'').type('a');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_EGRAVE_UC_CODE:
            (*doc).type('\'').type('E');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_EGRAVE_LC_CODE:
            (*doc).type('\'').type('e');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_IGRAVE_UC_CODE:
            (*doc).type('\'').type('I');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_IGRAVE_LC_CODE:
            (*doc).type('\'').type('i');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OGRAVE_UC_CODE:
            (*doc).type('\'').type('O');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OGRAVE_LC_CODE:
            (*doc).type('\'').type('o');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_UGRAVE_UC_CODE:
            (*doc).type('\'').type('U');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_UGRAVE_LC_CODE:
            (*doc).type('\'').type('u');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ACIRC_UC_CODE:
            (*doc).type('o').type('A');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ACIRC_LC_CODE:
            (*doc).type('o').type('a');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ECIRC_UC_CODE:
            (*doc).type('o').type('E');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ECIRC_LC_CODE:
            (*doc).type('o').type('E');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ICIRC_UC_CODE:
            (*doc).type('o').type('I');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_ICIRC_LC_CODE:
            (*doc).type('o').type('i');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OCIRC_UC_CODE:
            (*doc).type('o').type('A');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_OCIRC_LC_CODE:
            (*doc).type('o').type('o');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_UCIRC_UC_CODE:
            (*doc).type('o').type('U');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        case KeyboardEngine::KEY_UCIRC_LC_CODE:
            (*doc).type('o').type(' ');
            (*doc).setDocumentChanged(true);
            (*getTextEngine()).render();
            (*getVideoEngine()).display(TextRenderEngine::DISPLAY_CONTEXT_ID);
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
        default:
            TextRenderEngineKeyboardCallback::_ESCAPE_PRESSES_COUNT = 0;
            
            break;
    }

    return false;

}

void TextRenderEngineKeyboardCallback::toString()
{
    cout << "[TextRenderEngineKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextRenderEngineKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

TextRenderEngineKeyboardCallback::~TextRenderEngineKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextRenderEngineKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextRenderEngineKeyboardCallback::TextRenderEngineKeyboardCallback():
KeyboardCallback()
{

}




