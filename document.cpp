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
using std::strcpy;

#include "doc_row.hpp"
#include "document.hpp"
#include "app_globals.hpp"


void Document::setDocFileName(const char filename[] )
{
    _docFileName = new char[strlen(filename)];

    strcpy(_docFileName, filename);
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

Document & Document::addNewLine()
{
    return addNewLine(-1);
}

Document & Document::addNewLine(int pos)
{
    DocRow * newLinePtr = new DocRow;
    DocRow * lastLinePtr = 0;

    if (pos < 0 || getDocRowEOF() == 0)
    {
        if (getDocRowEOF() > 0) {
            lastLinePtr = rowAt(-1);
            (*lastLinePtr).setNextRowPtr(newLinePtr);
            (*newLinePtr).setPreviousRowPtr(lastLinePtr);
            (*newLinePtr).setNextRowPtr(0);
        } else {
            setStartRowPtr(newLinePtr);
        }
        setDocCol(0);
        setDocRowEOF(getDocRowEOF() + 1);
        setDocRow(getDocRowEOF());
        setCurrentRowPtr(newLinePtr);

    } else {

        if (pos > getDocRowEOF()) {
            pos = getDocRowEOF();
        }

        lastLinePtr = rowAt(pos);
        (*newLinePtr).setNextRowPtr((*lastLinePtr).getNextRowPtr());
        (*lastLinePtr).setNextRowPtr(newLinePtr);
        (*newLinePtr).setPreviousRowPtr(lastLinePtr);

        setDocCol(0);
        setDocRowEOF(getDocRowEOF() + 1);
        setDocRow(getDocRow()+1);
        setCurrentRowPtr(newLinePtr);

    }


    return (*this);
}

DocRow * Document::rowAt(int row)
{
    return rowAt(getStartRowPtr(), row);
}

DocRow * Document::rowAt(DocRow * docRowPtr, int offset)
{

    DocRow * foundRowPtr = 0;

    if (offset > 10000 || docRowPtr == 0) {
        return 0;
    }

    if (offset == 0) {
        return docRowPtr;
    } else if (offset < 0) {
        foundRowPtr = rowAt((*docRowPtr).getNextRowPtr(), -1);

        if(foundRowPtr == 0) {
            return docRowPtr;
        }
    } else {
        foundRowPtr = rowAt((*docRowPtr).getNextRowPtr(), --offset);

        if(foundRowPtr == 0) {
            return docRowPtr;
        }
    }

    return docRowPtr;
}

Document & Document::cursorMoveUp()
{
    setDocCol(0);
    setDocRow(getDocRow() - 1);

    if (getDocRow() < 0)
    {
        setDocRow(0);
    }

    if ((*getCurrentRowPtr()).getPreviousRowPtr() != 0)
    {
        setCurrentRowPtr((*getCurrentRowPtr()).getPreviousRowPtr());
    }

    return (*this);
}

Document & Document::cursorMoveDown()
{
    setDocCol(0);
    setDocRow(getDocRow() + 1);

    if (getDocRow() > getDocRowEOF())
    {
        setDocRow(getDocRowEOF());
    }

    if ((*getCurrentRowPtr()).getNextRowPtr() != 0)
    {
        setCurrentRowPtr((*getCurrentRowPtr()).getNextRowPtr());
    }

    return (*this);
}

Document & Document::cursorMoveStartOfLine()
{
    setDocCol(0);

    return (*this);
}

Document & Document::cursorMoveLeft()
{
    setDocCol(getDocCol() - 1);
    if (getDocCol() < 0)
    {
        cursorMoveUp();
    }

    return (*this);
}

Document & Document::cursorMoveRight()
{
    setDocCol(getDocCol() + 1);

    if (getDocCol() > (*getCurrentRowPtr()).getLength())
    {
        cursorMoveDown();
    }

    return (*this);
}

Document & Document::cursorMoveEndLine()
{
    setDocCol((*getCurrentRowPtr()).getLength());

    return (*this);
}

Document & Document::cursorMoveBegin()
{
    setDocCol(0);
    setDocRow(0);
    setCurrentRowPtr(getStartRowPtr());

    return (*this);
}


Document & Document::type(const char character)
{
    if (character == '\n')
    {
        addNewLine();
    } else if (character != '\0') {
        (*getCurrentRowPtr()).append(character, getDocCol());
        setDocCol(getDocCol()+1);
    }

    return (*this);
}

Document & Document::type(const char text[])
{
    for (int i = 0; i<strlen(text); i++)
    {
        if (text[i] == '\n')
        {
           addNewLine();
        } else if (text[i] != '\0')
        {
            (*getCurrentRowPtr()).append(text[i], getDocCol());
            setDocCol(getDocCol()+1);
        }
    }

    return (*this);
}

Document & Document::joinNextLine()
{
    DocRow *nextLinePtr = 0;
    DocRow *afterNextLinePtr = 0;
    DocCharacter * lastCurrentCharPtr = 0;
    DocCharacter * firstNextCharPtr = 0;

    nextLinePtr = (*getCurrentRowPtr()).getNextRowPtr();
    if (nextLinePtr == 0) {
        return (*this);
    }

    lastCurrentCharPtr = (*getCurrentRowPtr()).charPtrAtEnd();
    firstNextCharPtr = (*nextLinePtr).getStartCharPtr();

    (*lastCurrentCharPtr).setNextCharPtr(firstNextCharPtr);
    (*firstNextCharPtr).setPreviousCharPtr(lastCurrentCharPtr);
    //Gambiarra! :) Why not?
    (*lastCurrentCharPtr).setChar(' ');


    afterNextLinePtr = (*nextLinePtr).getNextRowPtr();
    if (afterNextLinePtr != 0)
    {
        cout << "Fuuudei!" << endl;
        (*getCurrentRowPtr()).setNextRowPtr(afterNextLinePtr);
        (*afterNextLinePtr).setPreviousRowPtr(getCurrentRowPtr());
    } else {
        (*getCurrentRowPtr()).setNextRowPtr(afterNextLinePtr);
    }

    delete nextLinePtr;

    return (*this);
}

Document & Document::triggerBackspace()
{
    DocCharacter * deadCandidatePtr = 0;
    DocCharacter * previousCharPtr = 0;
    DocCharacter * nextCharPtr = 0;

    if (getDocCol() == 0)
    {
        deadCandidatePtr = (*getCurrentRowPtr()).getStartCharPtr();
    } else {
        deadCandidatePtr = (*getCurrentRowPtr()).charPtrAt(getDocCol());
    }

    if (deadCandidatePtr == 0)
        return (*this);

    nextCharPtr = (*deadCandidatePtr).getNextCharPtr();
    if (nextCharPtr != 0)
    {
        previousCharPtr = (*deadCandidatePtr).getPreviousCharPtr();
        if ( previousCharPtr != 0)
        {
            (*previousCharPtr).setNextCharPtr((*deadCandidatePtr).getNextCharPtr());
            (*nextCharPtr).setPreviousCharPtr(previousCharPtr);
            setDocCol(getDocCol()-1);
            delete deadCandidatePtr;
        }
    } else {
        previousCharPtr = (*deadCandidatePtr).getPreviousCharPtr();
        if (previousCharPtr == 0)
        {
            /*cursorMoveUp();
            setDocCol((*getCurrentRowPtr()).getLength());
            joinNextLine();*/
            (*getCurrentRowPtr()).setStartCharPtr(0);
            delete deadCandidatePtr;
            setDocCol(0);
        } else {
            (*previousCharPtr).setNextCharPtr(0);
            setDocCol(getDocCol()-1);
            delete deadCandidatePtr;
        }
    }

    return (*this);
}


void Document::setCurrentRowPtr(DocRow * docRow)
{
    _currentRowPtr = docRow;
}

DocRow * Document::getCurrentRowPtr() const
{
    return _currentRowPtr;
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
_docFileName({"new_file.txt"}),
_currentRowPtr(0)
{
    addNewLine();
}

