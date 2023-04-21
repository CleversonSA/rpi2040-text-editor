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

#include "doc_character.hpp"
#include "app_globals.hpp"

void DocCharacter::setChar(const char character)
{
    _character = character;
}

void DocCharacter::setNextCharPtr(DocCharacter * docCharacter)
{
    _nextCharPtr = docCharacter;
}

void DocCharacter::setPreviousCharPtr(DocCharacter * docCharacter)
{
    _previousCharPtr = docCharacter;
}

char DocCharacter::getChar() const
{
    return _character;
}

DocCharacter* DocCharacter::getPreviousCharPtr() const
{
    return _previousCharPtr;
}

DocCharacter* DocCharacter::getNextCharPtr() const
{
    return _nextCharPtr;
}

void DocCharacter::toString()
{
    cout << "[DocCharacter] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << "[character=\"" << _character << "\"] "
         << "[previousCharPtr=" << _previousCharPtr << "] "
         << "[nextCharPtr=" << _nextCharPtr << "] "
         << endl;
}

int DocCharacter::getMemSize()
{
    return sizeof((*this));
}

DocCharacter::~DocCharacter()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[DocCharacter] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

DocCharacter::DocCharacter(char character, DocCharacter * nextCharPtr, DocCharacter * previousCharPtr):
CSAObject(),
_nextCharPtr(nextCharPtr),
_previousCharPtr(previousCharPtr),
_character(character)
{

}

