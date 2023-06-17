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
using std::memcpy;
using std::sprintf;

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


int Document::getDocRow() const
{
    volatile int rows = 1;

    DocRow *rPtr = getStartRowPtr();
    if (rPtr == 0) {
        return 0;
    }
    if ((*rPtr).getNextRowPtr() == 0) {
        return 1;
    }

    while (rPtr != 0)
    {
        if (rPtr == getCurrentRowPtr()){
            break;
        }

        if((*rPtr).getNextRowPtr() == 0)
        {
            break;
        }

        rPtr = (*rPtr).getNextRowPtr();
        rows++;

    }
    for (volatile int i = 0; i< rows; i++)
    {
        rPtr = (*rPtr).getPreviousRowPtr();
    }
    return rows;
}


int Document::getDocCol() const
{
    volatile int cols = 1;

    DocCharacter *cPtr = (*getCurrentRowPtr()).getStartCharPtr();

    if (cPtr == 0) {
        return 0;
    }
    if ((*cPtr).getNextCharPtr() == 0) {
        return 1;
    }
    while (cPtr !=0 )
    {
        if (cPtr == (*getCurrentRowPtr()).getCurrentCharPtr()){
            break;
        }

        if ((*cPtr).getNextCharPtr() == 0)
        {
            break;
        }

        cPtr = (*cPtr).getNextCharPtr();
        cols++;
    }
    for (volatile int i = 0; i< cols; i++)
    {
        cPtr = (*cPtr).getPreviousCharPtr();
    }

    return cols;
}


int Document::getDocRowEOF() const
{
    volatile int rows = 0;

    DocRow *rPtr = getStartRowPtr();
    if (rPtr == 0) {
        return 0;
    }
    if ((*rPtr).getNextRowPtr() == 0) {
        return 1;
    }
    while (rPtr != 0)
    {
        cout << "correndo linha " << rows << endl;

        if ((*rPtr).getNextRowPtr() == 0)
        {
            break;
        }

        rPtr = (*rPtr).getNextRowPtr();
        rows++;
    }
    for (volatile int i = 0; i<= rows; i++)
    {
        rPtr = (*rPtr).getPreviousRowPtr();
    }
    return rows+1;
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
    DocRow * newLinePtr = new DocRow;
    DocRow * lastLinePtr = 0;

    if (getDocRowEOF() > 0) {
        lastLinePtr = getCurrentRowPtr();
        (*newLinePtr).setNextRowPtr((*lastLinePtr).getNextRowPtr());

        DocRow *nextOfLastLine = (*lastLinePtr).getNextRowPtr();
        if (nextOfLastLine != 0) {
            (*nextOfLastLine).setPreviousRowPtr(newLinePtr);
        }
        (*newLinePtr).setPreviousRowPtr(lastLinePtr);
        (*lastLinePtr).setNextRowPtr(newLinePtr);

    } else {
        setStartRowPtr(newLinePtr);
    }

    setCurrentRowPtr(newLinePtr);

    return (*this);
}

Document & Document::addNewLine(int pos)
{

    DocRow * newLinePtr = new DocRow;
    DocRow * lastLinePtr = 0;

    if (pos > getDocRowEOF()) {
        pos = getDocRowEOF();
    }

    if (pos == 0) {
        lastLinePtr = getStartRowPtr();
    } else {
        lastLinePtr = rowAt(pos);
    }

    DocRow *previousRow = (*lastLinePtr).getPreviousRowPtr();

    (*newLinePtr).setPreviousRowPtr(previousRow);

    if (previousRow != 0)
    {
        (*previousRow).setNextRowPtr(newLinePtr);
    }

    (*newLinePtr).setNextRowPtr(lastLinePtr);
    (*lastLinePtr).setPreviousRowPtr(newLinePtr);

    DocCharacter *candidateDc = (*getCurrentRowPtr()).charPtrAt(getDocCol());

    DocCharacter *lastDc = (*candidateDc).getPreviousCharPtr();

    if (candidateDc != 0)
    {
        (*candidateDc).setPreviousCharPtr(0);
    }
    if ( lastDc != 0)
    {
        (*lastDc).setNextCharPtr(0);
    }

    if ((*lastLinePtr).getStartCharPtr() == candidateDc) {
        char aux = (*candidateDc).getChar();
        candidateDc = new DocCharacter(aux);
    }

    (*newLinePtr).setStartCharPtr((*lastLinePtr).getStartCharPtr());
    (*lastLinePtr).setStartCharPtr(candidateDc);

    if (pos == 1 || pos == 0) {
       setStartRowPtr(newLinePtr);
    }


    setCurrentRowPtr(rowAt(pos));
    cursorMoveDown();
    cursorMoveStartOfLine();

    return (*this);
}

DocRow * Document::rowAt(int row)
{
    return rowAt(getStartRowPtr(), row);
}

DocRow * Document::rowAt(DocRow * docRowPtr, int offset)
{

    DocRow * foundRowPtr = 0;

    if (offset < 0 && docRowPtr == 0) {
        return 0;
    }

    if (offset == 0) {
        return docRowPtr;

    } else if (offset < 0) {
        foundRowPtr = rowAt((*docRowPtr).getNextRowPtr(), -1);

        if(foundRowPtr == 0) {
            return docRowPtr;
        } else {
            return foundRowPtr;
        }
    } else {
        foundRowPtr = rowAt((*docRowPtr).getNextRowPtr(), --offset);

        if(foundRowPtr == 0) {
            return docRowPtr;
        }else {
            return foundRowPtr;
        }
    }

    return docRowPtr;
}

Document & Document::cursorMoveUp()
{

    if ((*getCurrentRowPtr()).getPreviousRowPtr() != 0)
    {
        setCurrentRowPtr((*getCurrentRowPtr()).getPreviousRowPtr());
    } else {
        setCurrentRowPtr(getCurrentRowPtr());
    }
    (*getCurrentRowPtr()).setCurrentCharPtr((*getCurrentRowPtr()).getLastCharPtr());

    return (*this);
}

Document & Document::cursorMoveDown()
{
    DocRow *nextOfCurrent = (*getCurrentRowPtr()).getNextRowPtr();
    if ( nextOfCurrent == 0 ) {
        setCurrentRowPtr(getCurrentRowPtr());
    }

    if ( nextOfCurrent != 0 ) {
        setCurrentRowPtr(nextOfCurrent);
    }

    (*getCurrentRowPtr()).setCurrentCharPtr((*getCurrentRowPtr()).getStartCharPtr());

    return (*this);
}

Document & Document::cursorMoveStartOfLine()
{
    (*getCurrentRowPtr()).setCurrentCharPtr((*getCurrentRowPtr()).getStartCharPtr());

    return (*this);
}

Document & Document::cursorMoveLeft()
{
    if ((*getCurrentRowPtr()).getCurrentCharPtr() == (*getCurrentRowPtr()).getStartCharPtr())
    {
        cursorMoveUp();
    } else {
        (*getCurrentRowPtr()).movePreviousCharPtr();
    }

    return (*this);
}

Document & Document::cursorMoveRight()
{
    (*getCurrentRowPtr()).moveNextCharPtr();
    if ((*getCurrentRowPtr()).isCurrentCharPtrAtEnd())
    {
        cursorMoveDown();
    }

    return (*this);
}

Document & Document::cursorMoveEndLine()
{
    volatile int cols = 0;

    DocCharacter *cPtr = (*getCurrentRowPtr()).getStartCharPtr();

    if (cPtr == 0) {
        return (*this);
    }
    if ((*cPtr).getNextCharPtr() == 0) {
        return (*this);
    }
    while ((*cPtr).getNextCharPtr()!=0)
    {
        cPtr = (*cPtr).getNextCharPtr();
        cols++;

        if ((*cPtr).getNextCharPtr() == 0){
            (*getCurrentRowPtr()).setCurrentCharPtr(cPtr);
            break;
        }
    }
    for (volatile int i = 0; i< cols; i++)
    {
        cPtr = (*cPtr).getPreviousCharPtr();
    }

    return (*this);
}

Document & Document::cursorMoveBegin()
{
    setCurrentRowPtr(getStartRowPtr());
    (*getCurrentRowPtr()).setCurrentCharPtr((*getCurrentRowPtr()).getStartCharPtr());

    return (*this);
}


Document & Document::type(const char character)
{
    if (character == '\n')
    {
        addNewLine();
    } else if (character != '\0') {
        (*getCurrentRowPtr()).append(character, getDocCol());
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


    deadCandidatePtr = (*getCurrentRowPtr()).getCurrentCharPtr();

    if (deadCandidatePtr == 0)
    {
        DocRow * currentRowPtr = getCurrentRowPtr();
        DocRow * previousRowPtr = (*getCurrentRowPtr()).getPreviousRowPtr();
        DocRow * nextRowPtr = (*getCurrentRowPtr()).getNextRowPtr();
        if (previousRowPtr != 0)
        {
            if(nextRowPtr != 0) {
                (*nextRowPtr).setPreviousRowPtr(previousRowPtr);
            }
            (*previousRowPtr).setNextRowPtr(nextRowPtr);
            delete currentRowPtr;

            setCurrentRowPtr(previousRowPtr);
            cursorMoveEndLine();
        }
        return (*this);
    }

    previousCharPtr = (*deadCandidatePtr).getPreviousCharPtr();
    nextCharPtr = (*deadCandidatePtr).getNextCharPtr();

    if(previousCharPtr != 0) {
        if (nextCharPtr != 0) {
            (*nextCharPtr).setPreviousCharPtr(previousCharPtr);
            (*getCurrentRowPtr()).setCurrentCharPtr(nextCharPtr);
        }
        (*previousCharPtr).setNextCharPtr(nextCharPtr);
        (*getCurrentRowPtr()).setCurrentCharPtr(previousCharPtr);
        delete deadCandidatePtr;
    } else {
        if (nextCharPtr != 0) {
            (*nextCharPtr).setPreviousCharPtr(0);
            (*getCurrentRowPtr()).setCurrentCharPtr(nextCharPtr);
            (*getCurrentRowPtr()).setStartCharPtr(nextCharPtr);
            delete deadCandidatePtr;
        } else {
            (*getCurrentRowPtr()).setCurrentCharPtr(0);
            (*getCurrentRowPtr()).setStartCharPtr(0);
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
_docFileName({"new_file.txt"}),
_currentRowPtr(0)
{
    addNewLine();
}

