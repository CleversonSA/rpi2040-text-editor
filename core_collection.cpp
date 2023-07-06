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

#include "core_collection.hpp"
#include "app_globals.hpp"

CoreCollection * CoreCollection::_me = 0;

Document * CoreCollection::getCurrentDocument()
{
    return _currentDocumentPtr;
}

TextRenderEngine * CoreCollection::getTextRenderEngine()
{
    return _textRenderEnginePtr;
}

TextPersistenceEngine * CoreCollection::getTextPersistenceEngine()
{
    return _textPersistenceEnginePtr;
}

OpenFileMenu * CoreCollection::getOpenFileMenu()
{
    return _openFileMenuPtr;
}

void CoreCollection::setCurrentDocument(Document *currentDocument)
{
    _currentDocumentPtr = currentDocument;
}

void CoreCollection::setTextRenderEngine(TextRenderEngine *textRenderEngine)
{
    _textRenderEnginePtr = textRenderEngine;
}

void CoreCollection::setTextPersistenceEngine(TextPersistenceEngine *textPersistenceEngine)
{
    _textPersistenceEnginePtr = textPersistenceEngine;
}

void CoreCollection::setOpenFileMenu(OpenFileMenu *openFileMenu)
{
    _openFileMenuPtr = openFileMenu;
}

void CoreCollection::toString()
{
    cout << "[CoreCollection] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int CoreCollection::getMemSize()
{
    return sizeof((*this));
}

CoreCollection::~CoreCollection()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[CoreCollection] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

CoreCollection& CoreCollection::getInstance()
{
    if (CoreCollection::_me == 0)
    {
        CoreCollection::_me = new CoreCollection();
    }
    return (*CoreCollection::_me);
}


CoreCollection::CoreCollection():
CSAObject(),
_openFileMenuPtr(0),
_textPersistenceEnginePtr(0),
_textRenderEnginePtr(0),
_currentDocumentPtr(0)
{

}

