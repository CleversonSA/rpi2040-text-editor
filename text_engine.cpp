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

#include "text_engine.hpp"
#include "app_globals.hpp"

void TextEngine::toString()
{
    cout << "[TextEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextEngine::getMemSize()
{
    return sizeof((*this));
}

TextEngine::~TextEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextEngine::TextEngine():
DocumentEngine()
{

}



