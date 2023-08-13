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

#include <cstring>
using std::strcmp;


#include <iomanip>
using std::setw;

#include "save_as_menu.hpp"
#include "../engine/splashbox_engine.hpp"
#include "../engine/msgbox_engine.hpp"
#include "../engine/inputbox_engine.hpp"
#include "../resource_collection.hpp"
#include "../core_collection.hpp"
#include "save_as_menu_keyboard_callback.hpp"
#include "text_persistence_engine.hpp"
#include "document.hpp"

void SaveAsMenu::run(bool forceFileName)
{
    Document *doc = CoreCollection::getInstance().getCurrentDocument();

    if (forceFileName || (*doc).isDefaultDocFilename())
    {
        showInputfileName();
    } else {
        save((*doc).getDocFileName());
    }

}

void SaveAsMenu::showConfirmOverwite()
{
    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();
    DiskEngine *disk = ResourceCollection::getInstance().getDiskEngine();
    MsgBoxEngine *msgbox = ResourceCollection::getInstance().getMsgBoxEngine();

    if ( getFileNameToSave() == 0 ||
        strcmp(getFileNameToSave(), "") == 0) {
        backToDocument();
        return;
    }

    int err = (*disk).openFile(AppGlobals::STORAGE_DOCUMENTS_DIR, getFileNameToSave(),DiskEngine::FILE_OPEN_READONLY);
    if (err >= 0) {
        SaveAsKeyboardCallback *cb = new SaveAsKeyboardCallback(this);
        (*cb).setSourceHandler(SaveAsKeyboardCallback::MSGBOX_OVERWRITE);

        char tmp[64];
        strcat(tmp, "Confirm overwrite [");strcat(tmp, getFileNameToSave());strcat(tmp,"]?");
        (*disk).closeFile();
        (*msgbox)
            .reset()
            .setTitle("Save As")
            .setMessage(tmp)
            .setIconType(MsgBoxEngine::QUESTION_ICON)
            .setButtonType(MsgBoxEngine::YESNOCANCEL_BUTTON)
            .render()
            .setCallback(cb)
            .run(video, keyboard);
    }

    cout << "Save acionado" << endl;
    save(getFileNameToSave());
}

void SaveAsMenu::setFileNameToSave(char * filename) {
    _fileNameToSave = new char[strlen(filename)+1];

    strcpy(_fileNameToSave, filename);
}

char * SaveAsMenu::getFileNameToSave()
{
    return _fileNameToSave;
}

void SaveAsMenu::showInputfileName()
{


    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();
    InputBoxEngine *inputBox = ResourceCollection::getInstance().getInputBoxEngine();

    SaveAsKeyboardCallback *cb = new SaveAsKeyboardCallback(this);
    Document *doc = CoreCollection::getInstance().getCurrentDocument();

    (*cb).setSourceHandler(SaveAsKeyboardCallback::INPUTBOX_FILENAME);

    (*inputBox)
            .reset()
            .setTitle("Save As...")
            .setCallback(cb)
            .setMessage("File name:")
            .setUserInput((*doc).getDocFileName())
            .render()
            .run(video, keyboard);

}

void SaveAsMenu::saveSilent(char * fileName)
{
    TextPersistenceEngine *textPersistenceEngine = CoreCollection::getInstance().getTextPersistenceEngine();
    Document *doc = CoreCollection::getInstance().getCurrentDocument();
    (*doc).setDocFileName(fileName);
    (*textPersistenceEngine).store();
    (*doc).setDocumentChanged(false);

}

void SaveAsMenu::save(char * fileName)
{
    UtilsEngine *utils = ResourceCollection::getInstance().getUtils();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();
    SplashBoxEngine *splashbox = ResourceCollection::getInstance().getSplashBoxEngine();

    saveSilent(fileName);

    (*splashbox)
        .reset()
        .setTitle("Save As")
        .setMessage("File saved!")
        .render();

    (*video).display();
    (*utils).sleepMs(1000);


    backToDocument();
}

void SaveAsMenu::backToDocument()
{

    TextRenderEngine *component = CoreCollection::getInstance().getTextRenderEngine();
    VideoEngine *video = ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboardEngine = ResourceCollection::getInstance().getKeyboardEngine();

    (*component)
            .render();
    (*component)
            .run(video, keyboardEngine);
}

void SaveAsMenu::toString()
{
    cout << "[SaveAsMenu] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int SaveAsMenu::getMemSize()
{
    return sizeof((*this));
}

SaveAsMenu::~SaveAsMenu()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[SaveAsMenu] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

SaveAsMenu::SaveAsMenu():
CSAObject()
{

}
