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
#include "../csa_object.hpp"
#include "open_file_menu_keyboard_callback.hpp"
#include "../engine/widget_engine.hpp"
#include "../engine/menu_engine.hpp"

void OpenFileMenuKeyboardCallback::execute(WidgetEngine * widgetEngine)
{

     if (strcmp((*widgetEngine).getResultCharValue1(),"DIR") == 0)
     {
         // FIX-ME: This will cause stack overflow
         (*_openFileMenuPtr).run();
         return;
     }

    (*_openFileMenuPtr).open((*widgetEngine).getResultCharValue1());

}


void OpenFileMenuKeyboardCallback::toString()
{
    cout << "[OpenFileMenuKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int OpenFileMenuKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

OpenFileMenuKeyboardCallback::~OpenFileMenuKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[OpenFileMenuKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

OpenFileMenuKeyboardCallback::OpenFileMenuKeyboardCallback(OpenFileMenu * openFileMenuPtr):
WidgetCallback(),
_openFileMenuPtr(openFileMenuPtr)
{

}




