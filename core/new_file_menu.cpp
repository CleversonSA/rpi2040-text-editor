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

#include "new_file_menu.hpp"
#include "document.hpp"
#include "../resource_collection.hpp"
#include "../core_collection.hpp"
#include "new_file_menu_keyboard_callback.hpp"
#include "text_render_engine.hpp"


void NewFileMenu::backToDocument()
{

    TextRenderEngine *component = CoreCollection::getInstance().getTextRenderEngine();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboardEngine = ResourceCollection::getInstance().getKeyboardEngine();

    (*component)
            .render();
    (*component)
            .run(video, keyboardEngine);
}


void NewFileMenu::run()
{

    NewFileMenuKeyboardCallback *cb = new NewFileMenuKeyboardCallback(this);

    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();
    Document *doc = CoreCollection::getInstance().getCurrentDocument();

    MsgBoxEngine *msgBoxEngine = ResourceCollection::getInstance().getMsgBoxEngine();

    if ((*doc).hasDocumentChanged()) {
        (*msgBoxEngine)
            .reset()
            .setTitle("New file")
            .setMessage("Save current changes?")
            .setIconType(MsgBoxEngine::QUESTION_ICON)
            .setButtonType(MsgBoxEngine::YESNOCANCEL_BUTTON)
            .setCallback(cb)
            .render()
            .run(video, keyboard);
    } else {
        prepareNewDocument();
    }

    delete cb;
}

void NewFileMenu::prepareNewDocument() {
    UtilsEngine *utils = ResourceCollection::getInstance().getUtils();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();

    AppGlobals::getInstance().setLastOpennedDocument(0);
    AppGlobals::getInstance().setNewFileCalled(true);
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

void NewFileMenu::toString()
{
    cout << "[NewFileMenu] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int NewFileMenu::getMemSize()
{
    return sizeof((*this));
}

NewFileMenu::~NewFileMenu()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[NewFileMenu] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

NewFileMenu::NewFileMenu():
CSAObject()
{

}
