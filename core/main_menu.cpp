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

#include "main_menu.hpp"
#include "../resource_collection.hpp"
#include "main_menu_keyboard_callback.hpp"

void MainMenu::run()
{

    MainMenuKeyboardCallback *cb = new MainMenuKeyboardCallback(this);

    MenuEngine *menu = ResourceCollection::getInstance().getMenuEngine();
    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();

    char *mainMenuStr = new char[255];
    mainMenuStr[0] = '\0';

    strcat(mainMenuStr, "NEW_FILE");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    strcat(mainMenuStr, "New document");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DELIM);

    strcat(mainMenuStr, "OPEN_FILE");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    strcat(mainMenuStr, "Open...");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DELIM);

    strcat(mainMenuStr, "SAVE_FILE");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    strcat(mainMenuStr, "Save..");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DELIM);

    strcat(mainMenuStr, "SAVE_FILE_AS");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    strcat(mainMenuStr, "Save doc as...");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DELIM);

    strcat(mainMenuStr, "ABOUT");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    strcat(mainMenuStr, "About");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DELIM);

    strcat(mainMenuStr, "BACK_DOC");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    strcat(mainMenuStr, "<< Back to edit...");
    strcat(mainMenuStr, AppGlobals::MENU_ITEM_DELIM);

    (*menu)
            .reset()
            .setTitle("Main menu")
            .parseMenuString(mainMenuStr)
            .setCallback(cb)
            .render()
            .run(video, keyboard);

    delete cb;
}


void MainMenu::toString()
{
    cout << "[MainMenu] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int MainMenu::getMemSize()
{
    return sizeof((*this));
}

MainMenu::~MainMenu()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MainMenu] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MainMenu::MainMenu():
CSAObject()
{

}
