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
#include "main_menu_keyboard_callback.hpp"
#include "../core_collection.hpp"
#include "../resource_collection.hpp"
#include "../core/main_menu.hpp"

void MainMenuKeyboardCallback::execute(WidgetEngine * widgetEngine)
{
    // HIT ESC
    if ((*widgetEngine).getResultBoolValue() == false ) {
        if (strcmp((*widgetEngine).getResultCharValue1(), "FILE") == 0) {
            // FIX-ME: This will cause stack overflow
            (*_mainMenuPtr).showFileMenu();
            return;
        }

        if (strcmp((*widgetEngine).getResultCharValue1(), "SAVE_FILE") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getSaveAsMenu()).run(false);
            return;
        }


        if (strcmp((*widgetEngine).getResultCharValue1(), "SAVE_FILE_AS") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getSaveAsMenu()).run(true);
            return;
        }

        if (strcmp((*widgetEngine).getResultCharValue1(), "NEW_FILE") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getNewFileMenu()).run();
            return;
        }

        if (strcmp((*widgetEngine).getResultCharValue1(), "OPEN_FILE") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getOpenFileMenu()).run();
            return;
        }

        if (strcmp((*widgetEngine).getResultCharValue1(), "OPEN_FILE") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getOpenFileMenu()).run();
            return;
        }

        if (strcmp((*widgetEngine).getResultCharValue1(), "ABOUT") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getAbout()).run();
            return;
        }

        if (strcmp((*widgetEngine).getResultCharValue1(), "_BACK_") == 0) {
            // FIX-ME: This will cause stack overflow
            (*CoreCollection::getInstance().getTextRenderEngine()).run(
                    ResourceCollection::getInstance().getVideoEngine(),
                    ResourceCollection::getInstance().getKeyboardEngine()
            );
            return;
        }
    } else {
        // FIX-ME: This will cause stack overflow
        (*CoreCollection::getInstance().getTextRenderEngine()).run(
                ResourceCollection::getInstance().getVideoEngine(),
                ResourceCollection::getInstance().getKeyboardEngine()
        );
        return;
    }

}


void MainMenuKeyboardCallback::toString()
{
    cout << "[MainMenuKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int MainMenuKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

MainMenuKeyboardCallback::~MainMenuKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MainMenuKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MainMenuKeyboardCallback::MainMenuKeyboardCallback(MainMenu * mainMenuPtr):
WidgetCallback(),
_mainMenuPtr(mainMenuPtr)
{

}




