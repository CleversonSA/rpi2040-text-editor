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

#include "doc_row.hpp"

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
    return DocRow::charPtrAtEnd(getStartCharPtr());
}

DocCharacter * DocRow::charPtrAtEnd(DocCharacter * startCharPtr)
{
    DocCharacter *currentCharPtr = 0;

    if(startCharPtr == 0) {
        return 0;
    }

    currentCharPtr = DocRow::charPtrAtEnd((*startCharPtr).getNextCharPtr());
    if (currentCharPtr == 0)
    {
        return startCharPtr;
    }
}

DocCharacter * DocRow::charPtrAt(int pos)
{
    return DocRow::charPtrAt(getStartCharPtr(), pos);
}


DocCharacter * DocRow::charPtrAt(DocCharacter * startCharPtr, int pos)
{
    DocCharacter *currentCharPtr = 0;

    if(pos < 0 || startCharPtr == 0) {
        return 0;
    }

    currentCharPtr = DocRow::charPtrAt((*startCharPtr).getNextCharPtr(), --pos);
    if (currentCharPtr == 0)
    {
        return startCharPtr;
    }
}

DocRow & DocRow::deletePtrAt(int pos)
{
    DocCharacter *currentCharPtr = 0;
    DocCharacter *nextCharPtr = 0;
    DocCharacter *previousCharPtr = 0;

    currentCharPtr = DocRow::charPtrAt(getStartCharPtr(), pos);
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

DocRow & DocRow::append(DocCharacter * charPtr)
{
    DocCharacter * lastCharPtr = DocRow::charPtrAtEnd(getStartCharPtr());

    (*lastCharPtr).setNextCharPtr(charPtr);
    (*charPtr).setPreviousCharPtr(lastCharPtr);
    (*lastCharPtr).setChar((*charPtr).getChar());
    (*charPtr).setChar('\0');
    (*charPtr).setNextCharPtr(0);

    return (*this);
}


void DocRow::toString()
{
    cout << "[DocRow] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << "[startCharPtr=" << getStartCharPtr() << "] "
         << "[previousRowPtr=" << getPreviousRowPtr() << "] "
         << "[nextRowPtr=" << getNextRowPtr() << "] "
         << endl;
}

DocRow::~DocRow()
{
    cout << "[DocRow] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
}

DocRow::DocRow(DocCharacter * startCharPtr, DocRow * nextRowPtr, DocRow * previousRowPtr):
CSAObject(),
_nextRowPtr(nextRowPtr),
_previousRowPtr(previousRowPtr),
_startCharPtr(startCharPtr)
{

}

