
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

#include <iomanip>
using std::setw;

#include <cstring>
using std::strlen;
using std::strtok;

#include "textview_engine.hpp"
#include "video_engine.hpp"
#include "keyboard_engine.hpp"
#include "../keyboard/textview_keyboard_callback.hpp"


void TextViewEngine::run(VideoEngine *videoEngine, KeyboardEngine *keyboardEngine)
{
    //(*videoEngine).display();

    TextViewKeyboardCallback *kcb = new TextViewKeyboardCallback;

    (*kcb).setVideoEngine(videoEngine);
    (*kcb).setTextViewEngine(this);

    (*keyboardEngine).setup();
    (*keyboardEngine).setCallback(kcb);
    (*keyboardEngine).loop();

    delete kcb;
}

TextViewEngine & TextViewEngine::setTitle(const char title[])
{
    (*_menuEngineInstance).setTitle(title);

    return (*this);
}


char * TextViewEngine::getTitle() const
{
    return (*_menuEngineInstance).getTitle();
}


int TextViewEngine::getViewLinesCount() const
{
    return (*_menuEngineInstance).getMenuItemCount();
}

int TextViewEngine::getViewLinePos() const
{
    return (*_menuEngineInstance).getMenuItemPos();
}

TextViewEngine & TextViewEngine::parseViewString(char * viewString)
{
    if (strlen(viewString) > AppGlobals::MAX_VIEW_TEXT_SIZE)
    {
        cout << "Text size overflow!" << AppGlobals::MAX_VIEW_TEXT_SIZE << " bytes is maximum!" << endl;
        return (*this);
    }

    char *viewStringCpy = new char[strlen(viewString)+1];
    char *textArea = new char[AppGlobals::MAX_VIEW_TEXT_SIZE];
    char *lineId = 0;

    (*textArea) = '\0';
    int viewLinePos = 0;

    // So I think this will create a memory leak, since everytime this command is called
    // a new string is created. But, I think strtok will just assign the string tokens
    // to each pointer. To test it, call parseMenuString so many times until a memory
    // crash o.O
    strcpy(viewStringCpy, viewString);
    char *ptr = strtok(viewStringCpy, "\n");

	while(ptr != 0)
	{
	    if (viewLinePos > AppGlobals::MAX_MENU_ITEMS_COUNT)
        {
            break;
	    }

	    lineId = new char[5];
	    (*lineId) = '\0';

	    sprintf(lineId, "%d;", viewLinePos);
	    strcat(textArea, lineId);
	    strcat(textArea, ptr);
	    strcat(textArea, "|");

		ptr = strtok(0, "\n");

		viewLinePos++;
	}

	(*_menuEngineInstance).parseMenuString(textArea);

    return (*this);
}


char ** TextViewEngine::getTextLines()
{
    return (*_menuEngineInstance).getMenuItems();
}


char * TextViewEngine::getTextLine(const int linePos) const
{
    return (*_menuEngineInstance).getMenuItemLabel(linePos);
}


TextViewEngine & TextViewEngine::cursorMoveDown()
{
    (*_menuEngineInstance).cursorMoveDown();

    return (*this);
}

TextViewEngine & TextViewEngine::cursorMoveUp()
{
   (*_menuEngineInstance).cursorMoveUp();

    return (*this);
}

TextViewEngine & TextViewEngine::closeView()
{
    return (*this);
}


TextViewEngine & TextViewEngine::reset()
{
    (*_menuEngineInstance).reset();

    return (*this);
}


TextViewEngine::~TextViewEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextViewEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextViewEngine::TextViewEngine(MenuEngine * menuEngineInstance):
WidgetEngine(),
_menuEngineInstance(menuEngineInstance)
{
    if (menuEngineInstance == 0)
    {
        cout << "No menu engine instance!" << endl;
        return;
    }


}


