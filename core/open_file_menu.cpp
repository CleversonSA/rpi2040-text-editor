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

#include "open_file_menu.hpp"
#include "../app_globals.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/video_engine.hpp"
#include "document.hpp"
#include "../engine/disk_engine.h"
#include "../engine/menu_engine.hpp"
#include "../engine/splashbox_engine.hpp"
#include "../resource_collection.hpp"
#include "../core_collection.hpp"
#include "open_file_menu_keyboard_callback.hpp"
#include "text_persistence_engine.hpp"

void OpenFileMenu::run()
{

    OpenFileMenuKeyboardCallback *cb = new OpenFileMenuKeyboardCallback(this);

    DiskEngine *disk = ResourceCollection::getInstance().getDiskEngine();
    MenuEngine *menu = ResourceCollection::getInstance().getMenuEngine();
    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();

    char *filesStr = (*disk).dir(AppGlobals::STORAGE_DOCUMENTS_DIR);

    cout << "Arquivos: " << filesStr << endl;

    (*menu)
        .reset()
        .setTitle("Open file")
        .parseMenuString(filesStr)
        .setCallback(cb)
        .render()
        .run(video, keyboard);
}

void OpenFileMenu::open(char * fileName)
{
    TextPersistenceEngine *persistence = CoreCollection::getInstance().getTextPersistenceEngine();
    Document *doc = CoreCollection::getInstance().getCurrentDocument();
    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();
    TextRenderEngine *text = CoreCollection::getInstance().getTextRenderEngine();

    (*persistence).setDocument(doc);
    (*persistence).load(fileName);

    // Callbacks callbacks, I see callbacks everytime....
    cout << "chegou " << endl;
    (*text)
        .run(video, keyboard);
}

void OpenFileMenu::toString()
{
    cout << "[OpenFileMenu] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int OpenFileMenu::getMemSize()
{
    return sizeof((*this));
}

OpenFileMenu::~OpenFileMenu()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[OpenFileMenu] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

OpenFileMenu::OpenFileMenu():
CSAObject()
{

}
