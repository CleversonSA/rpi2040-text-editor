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
using std::sprintf;

#include "text_persistence_engine.hpp"
#include "engine/disk_engine.h"

int TextPersistenceEngine::load(const char *fileName)
{
    int err = (*getDiskEngine()).openFile(AppGlobals::STORAGE_DOCUMENTS_DIR,
                                          fileName,
                                DiskEngine::FILE_OPEN_READONLY);
    int byteCounter = 0;
    if (err < 0)
    {
        cout << "Error " << err << endl;
        return err;
    }

    (*getDocument()).destroy();
    //Workaround to avoid nullptr
    (*getDocument()).addNewLine();
    (*getDocument()).type(" ");
    (*getDocument()).setDocFileName(fileName);

    int fileSize = (*getDiskEngine()).getOpenedFileSize();
    for (byteCounter = 0; byteCounter < fileSize; byteCounter++)
    {
        char c = (*getDiskEngine()).read();
        if (c == '\n')
        {
            (*getDocument()).addNewLine();
        } else {
            (*getDocument()).type(c);
        }

    }

    (*getDiskEngine()).closeFile();

    return 0;
}

int TextPersistenceEngine::store()
{
    int err = (*getDiskEngine()).openFile(AppGlobals::STORAGE_DOCUMENTS_DIR,
                                (*getDocument()).getDocFileName(),
                                DiskEngine::FILE_OPEN_CREATE | DiskEngine::FILE_OPEN_READWRITE);
    if (err < 0)
    {
        return err;
    }
    render();

    (*getDiskEngine()).closeFile();
    return 0;
}


DiskEngine * TextPersistenceEngine::getDiskEngine() const
{
    return _diskEngine;
}

bool TextPersistenceEngine::isCursorAtBottomOfView() const
{
    return false;
}

bool TextPersistenceEngine::isCursorAtEndOfViewLine() const
{
    return false;
}

void TextPersistenceEngine::renderClearView()
{
    // Not applied
}

void TextPersistenceEngine::renderClearLine()
{
    // Not applied
}

void TextPersistenceEngine::renderLineBreak()
{
    (*getDiskEngine()).write('\n');
}

void TextPersistenceEngine::renderCarriageReturn()
{
    //Not applied
}

void TextPersistenceEngine::renderCursor()
{
    //Not applied
}

void TextPersistenceEngine::renderTabulation()
{
    (*getDiskEngine()).write('\t');
}

void TextPersistenceEngine::renderLineOverflowIndicator()
{
    //Not applied
}

void TextPersistenceEngine::renderLineWithOverflowIndicator()
{
    //Not applied
}

void TextPersistenceEngine::renderEmptyLineIndicator()
{
    //(*getDiskEngine()).write('\n');
}

void TextPersistenceEngine::renderLineWithContentIndicator()
{
    //Not applied
}

void TextPersistenceEngine::renderEOF()
{
    (*getDiskEngine()).write('\n');
}

void TextPersistenceEngine::renderCharacter(DocCharacter *dc)
{
    (*getDiskEngine()).write((*dc).getChar());
}

void TextPersistenceEngine::renderColRow(int row, int col, int bytes)
{
    //Not applied
}

void TextPersistenceEngine::toString()
{
    cout << "[TextPersistenceEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextPersistenceEngine::getMemSize()
{
    return sizeof((*this));
}

TextPersistenceEngine::~TextPersistenceEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextPersistenceEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextPersistenceEngine::TextPersistenceEngine(Document * document, DiskEngine *diskEngine):
DocumentEngine(document),
_diskEngine(diskEngine)
{

}


