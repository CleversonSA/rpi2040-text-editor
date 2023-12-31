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
#include "../engine/splashbox_engine.hpp"
#include "../engine/msgbox_engine.hpp"
#include "../resource_collection.hpp"
#include "../core_collection.hpp"
#include "open_file_menu_keyboard_callback.hpp"
#include "text_persistence_engine.hpp"
#include "document.hpp"

void OpenFileMenu::run()
{
    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();
    Document *doc = CoreCollection::getInstance().getCurrentDocument();
    MsgBoxEngine *msgbox = ResourceCollection::getInstance().getMsgBoxEngine();


    if ((*doc).hasDocumentChanged()) {
        //I see memory leaks...how often? Everytime!
        OpenFileMenuKeyboardCallback *cb = new OpenFileMenuKeyboardCallback(this);
        (*cb).setSourceHandler(OpenFileMenuKeyboardCallback::MSGBOX_SAVE_CHANGES);
        (*msgbox)
            .reset()
            .setTitle("Open file")
            .setMessage("Save current changes?")
            .setIconType(MsgBoxEngine::QUESTION_ICON)
            .setButtonType(MsgBoxEngine::YESNOCANCEL_BUTTON)
            .setCallback(cb)
            .render()
            .run(video, keyboard);

    } else {
        showMenu();
    }

}

void OpenFileMenu::saveDocument() {
    Document *doc = CoreCollection::getInstance().getCurrentDocument();

    (*CoreCollection::getInstance().getSaveAsMenu()).saveSilent((*doc).getDocFileName());
    showMenu();
}


void OpenFileMenu::showMenu()
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

    delete cb;
}

void OpenFileMenu::open(char * fileName)
{
    UtilsEngine *utils = ResourceCollection::getInstance().getUtils();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();

    AppGlobals::getInstance().setLastOpennedDocument(fileName);
    AppGlobals::getInstance().saveConstants();

    /**
     * Ok, let´s explain a litte about soft reset when loading file. Microcontrollers has a big problem
     * with memory fragmentation. I tried to clean up the document many times, but even with almost
     * 80% memory free, I got malloc errors due the fragmentation. The same problem I has with
     * Micropython, so, instead of create a large document to allocate memory at startup
     * just reboot the microcontroller. To end user, will looks like a normal usage flow. Beautiful, not
     * , but come on, it´s a microcontroller not a x86 PC (may be future?)
     */
    (*video).reset();
    (*utils).sleepMs(1000);
    (*utils).softReset();

}

void OpenFileMenu::backToDocument()
{

    TextRenderEngine *component = CoreCollection::getInstance().getTextRenderEngine();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboardEngine = ResourceCollection::getInstance().getKeyboardEngine();

    (*component)
            .render();
    (*component)
            .run(video, keyboardEngine);
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
