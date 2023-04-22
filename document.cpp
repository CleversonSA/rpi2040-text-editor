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

#include "doc_row.hpp"
#include "document.hpp"
#include "app_globals.hpp"


void Document::setDocFileName(char * docFileName)
{
    _docFileName = docFileName;
}

char * Document::getDocFileName() const
{
    return _docFileName;
}

void Document::setDocRow(const int docRow)
{
    _docRow = docRow;
}

int Document::getDocRow() const
{
    return _docRow;
}

void Document::setDocCol(const int docCol)
{
    _docCol = docCol;
}

int Document::getDocCol() const
{
    return _docCol;
}

void Document::setDocRowEOF(const int docRowEOF)
{
    _docRowEOF = docRowEOF;
}

int Document::getDocRowEOF() const
{
    return _docRowEOF;
}

void Document::setStartRowPtr(DocRow * docRowPtr)
{
    _startRowPtr = docRowPtr;
}

DocRow * Document::getStartRowPtr() const
{
    return _startRowPtr;
}


DocRow * Document::rowAt(int row)
{
    return 0;
}

DocRow * Document::rowAt(DocRow *, int)
{
    return 0;
}


Document & Document::addNewLine()
{
    return (*this);
}

Document & Document::triggerBackspace()
{
    return (*this);
}

Document & Document::cursorMoveUp()
{
    return (*this);
}

Document & Document::cursorMoveDown()
{
    return (*this);
}

Document & Document::cursorMoveLeft()
{
    return (*this);
}

Document & Document::cursorMoveRight()
{
    return (*this);
}

Document & Document::type(const char text[])
{
    return (*this);
}

void Document::toString()
{
    cout << "[Document] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Document::getMemSize()
{
    return sizeof((*this));
}

Document::~Document()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Document] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Document::Document():
CSAObject(),
_startRowPtr(0),
_docRow(0),
_docCol(0),
_docRowEOF(0),
_docFileName({"new_file.txt"})
{
    addNewLine();
}

