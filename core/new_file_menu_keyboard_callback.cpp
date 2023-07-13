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
#include <cstdio>
using std::sprintf;

#include <cstring>
using std::strcmp;

#include <iostream>
using std::cout;
using std::endl;

#include "../app_globals.hpp"
#include "../engine/widget_engine.hpp"
#include "../core_collection.hpp"
#include "../resource_collection.hpp"
#include "new_file_menu_keyboard_callback.hpp"

void NewFileMenuKeyboardCallback::execute(WidgetEngine * widgetEngine)
{
    switch((*widgetEngine).getResultIntValue())
    {
        case MsgBoxEngine::BTN_YES:
            (*_newFileMenuPtr).saveDocument();
            break;

        case MsgBoxEngine::BTN_NO:
            (*_newFileMenuPtr).prepareNewDocument();
            break;

        case MsgBoxEngine::BTN_CANCEL:
        default:
            (*_newFileMenuPtr).backToDocument();
            break;
    }

}


void NewFileMenuKeyboardCallback::toString()
{
    cout << "[NewFileMenuKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int NewFileMenuKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

NewFileMenuKeyboardCallback::~NewFileMenuKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[NewFileMenuKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

NewFileMenuKeyboardCallback::NewFileMenuKeyboardCallback(NewFileMenu * newFileMenuPtr):
WidgetCallback(),
_newFileMenuPtr(newFileMenuPtr)
{

}




