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
#include "app_globals.hpp"

void DocRow::setStartCharPtr(DocCharacter * startCharPtr)
{
    _startCharPtr = startCharPtr;
}

void DocRow::setNextRowPtr(DocRow * nextRowPtr)
{
    _nextRowPtr = nextRowPtr;
}

void DocRow::setPreviousRowPtr(DocRow * previousRowPtr)
{
    _previousRowPtr = previousRowPtr;
}

DocCharacter * DocRow::getStartCharPtr() const
{
    return _startCharPtr;
}

DocRow * DocRow::getPreviousRowPtr() const
{
    return _previousRowPtr;
}

DocRow* DocRow::getNextRowPtr() const
{
    return _nextRowPtr;
}

DocCharacter * DocRow::charPtrAtEnd()
{
    return charPtrAtEnd(getStartCharPtr());
}

DocCharacter * DocRow::charPtrAtEnd(DocCharacter * startCharPtr)
{
    DocCharacter *currentCharPtr = 0;

    if(startCharPtr == 0) {
        return 0;
    }

    currentCharPtr = charPtrAtEnd((*startCharPtr).getNextCharPtr());
    if (currentCharPtr == 0)
    {
        return startCharPtr;
    }

    return currentCharPtr;
}

DocCharacter * DocRow::charPtrAt(int pos)
{
    return charPtrAt(getStartCharPtr(), pos);
}


DocCharacter * DocRow::charPtrAt(DocCharacter * startCharPtr, int pos)
{
    DocCharacter *currentCharPtr = 0;

    if (pos == 0 && startCharPtr != 0) {
        return startCharPtr;
    } else if(pos < 0 && startCharPtr != 0) {
        return startCharPtr;
    } else if (pos < 0 || startCharPtr == 0) {
        return 0;
    }
    pos--;
    currentCharPtr = charPtrAt((*startCharPtr).getNextCharPtr(), pos);
    if (currentCharPtr == 0)
    {
        return startCharPtr;
    }

    return currentCharPtr;
}

DocRow & DocRow::deletePtrAt(int pos)
{
    DocCharacter *currentCharPtr = 0;
    DocCharacter *nextCharPtr = 0;
    DocCharacter *previousCharPtr = 0;

    currentCharPtr = charPtrAt(getStartCharPtr(), pos);
    if (currentCharPtr == 0)
    {
        cout << "[DOC ROW] [Error] [Position not found:" << pos << "]" << endl;
        return (*this);
    }

    nextCharPtr = (*currentCharPtr).getNextCharPtr();
    previousCharPtr = (*currentCharPtr).getPreviousCharPtr();


    if (previousCharPtr != 0)
    {
        (*previousCharPtr).setNextCharPtr(nextCharPtr);
    }

    if (nextCharPtr != 0)
    {
        (*nextCharPtr).setPreviousCharPtr(previousCharPtr);
    }

    if (currentCharPtr == getStartCharPtr())
    {
        setStartCharPtr(nextCharPtr);
        (*nextCharPtr).setPreviousCharPtr(0);
        delete currentCharPtr;

    } else {
        delete(currentCharPtr);
    }
    return (*this);

}

DocRow & DocRow::append(const char character, int pos)
{
   DocCharacter *dc = new DocCharacter(character);

   return append(dc, pos);
}

DocRow & DocRow::append(const char character)
{
   DocCharacter *dc = new DocCharacter(character);

   return append(dc);
}

DocRow & DocRow::append(const char charSequence[])
{
   return append(charSequence, -1);
}

DocRow & DocRow::append(const char charSequence[], int pos)
{
    DocCharacter * newChar = 0;
    for (int i=0; i< strlen(charSequence); i++)
    {
        if (charSequence[i] != '\0')
        {
            newChar = new DocCharacter(charSequence[i]);
            if (pos > 0)
            {
                append(newChar, pos);
                pos++;
            } else {
                append(newChar);
            }
        }
    }

    return (*this);
}

DocRow & DocRow::append(DocCharacter * charPtr)
{
    return append(charPtr, -1);
}

DocRow & DocRow::append(DocCharacter * charPtr, int pos)
{
    DocCharacter * lastCharPtr = 0;
    char aux = '\0';

    if (pos <= 0)
    {
        if (_startCharPtr != 0)
        {
            lastCharPtr = charPtrAtEnd(_startCharPtr);

            (*lastCharPtr).setNextCharPtr(charPtr);
            (*charPtr).setPreviousCharPtr(lastCharPtr);
            (*lastCharPtr).setChar((*charPtr).getChar());
            (*charPtr).setChar('\0');
            (*charPtr).setNextCharPtr(0);
        } else {
            (*charPtr).setNextCharPtr(0);
            (*charPtr).setPreviousCharPtr(0);
            _startCharPtr = charPtr;
        }
    } else {
        lastCharPtr = charPtrAt(pos);
        cout << (*lastCharPtr).getChar() << endl;


        if ((*lastCharPtr).getNextCharPtr() == 0) {
            (*charPtr).setNextCharPtr(0);
            (*lastCharPtr).setNextCharPtr(charPtr);
            (*charPtr).setPreviousCharPtr(lastCharPtr);
        } else {
            (*charPtr).setNextCharPtr((*lastCharPtr).getNextCharPtr());
            (*lastCharPtr).setNextCharPtr(charPtr);
            (*charPtr).setPreviousCharPtr(lastCharPtr);
            //aux = (*lastCharPtr).getChar();
            //(*lastCharPtr).setChar((*charPtr).getChar());
            (*charPtr).setChar(aux);
        }
    }

    return (*this);
}

void DocRow::fromCharArray(const char charArray [])
{
    fromCharArray(charArray, (*this));
}

void DocRow::fromCharArray(const char charArray [], DocRow &docRow)
{
    DocCharacter *startRowPtr = 0;
    DocCharacter *dc = 0;
    DocCharacter *previousPtr = 0;

    for (int i = 0; i<strlen(charArray)+1; i++) {
        dc = new DocCharacter(charArray[i]);

        if (startRowPtr == 0) {
            startRowPtr = dc;
        } else {
            (*previousPtr).setNextCharPtr(dc);
            (*dc).setPreviousCharPtr(previousPtr);
        }
        previousPtr = dc;
    }

    docRow.setStartCharPtr(startRowPtr);
}

void DocRow::readAllChars ()
{
    readAllChars(getStartCharPtr());
}

void DocRow::readAllChars (const DocCharacter * startCharPtr)
{
    static int fuse = 10000;

    fuse--;
    if (fuse < 0)
        return;

    if (startCharPtr != 0) {
        if ((*startCharPtr).getChar() != '\0')
        {
            cout << (*startCharPtr).getChar();
        }
    } else {
        fuse = 10000;
        return;
    }

    readAllChars((*startCharPtr).getNextCharPtr());
}

int DocRow::getLength () const
{
    return getLength(getStartCharPtr(), 0);
}

int DocRow::getLength (const DocCharacter * startCharPtr, int qtLength) const
{

    if (startCharPtr != 0) {
       return getLength((*startCharPtr).getNextCharPtr(), ++qtLength);
    } else {
       return qtLength;
    }

}

int DocRow::getSize()
{
    return getSize(getStartCharPtr());
}

int DocRow::getSize (const DocCharacter * startCharPtr)
{
    static int fuse = 10000;
    int total = 0;

    fuse--;
    if (fuse < 0)
        return 0;

    if (startCharPtr != 0) {
        total = sizeof((*startCharPtr));
    } else {
        fuse = 10000;
        return total;
    }

    return total + getSize((*startCharPtr).getNextCharPtr());
}


void DocRow::deleteAllChars()
{
    deleteAllChars(getStartCharPtr());
}

void DocRow::deleteAllChars (const DocCharacter * startCharPtr)
{
    static int fuse = 10000;

    fuse--;
    if (fuse < 0)
        return;

    if (startCharPtr != 0) {
        deleteAllChars((*startCharPtr).getNextCharPtr());
        delete startCharPtr;
    } else {
        fuse = 10000;
        return;
    }

}

void DocRow::toString()
{
    cout << "[DocRow] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << "[Addr=" << &(*this) << "] "
         << "[startCharPtr=" << getStartCharPtr() << "] "
         << "[previousRowPtr=" << getPreviousRowPtr() << "] "
         << "[nextRowPtr=" << getNextRowPtr() << "] "
         << endl;
}

int DocRow::getMemSize()
{
    return sizeof((*this)) + getSize();
}

DocRow::~DocRow()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[DocRow] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

DocRow::DocRow(DocCharacter * startCharPtr, DocRow * nextRowPtr, DocRow * previousRowPtr):
CSAObject(),
_nextRowPtr(nextRowPtr),
_previousRowPtr(previousRowPtr),
_startCharPtr(startCharPtr)
{
    /*DocCharacter *dc = new DocCharacter('\0');

    setStartCharPtr(dc);*/
}

