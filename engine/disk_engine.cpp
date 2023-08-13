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
#include "disk_engine.h"
#include "../app_globals.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <cstring>
using std::strcat;

#include <cstdio>
using std::sprintf;

DiskEngine * DiskEngine::_diskEngineInstance = 0;

//=================== CLASS IMPLEMENTATION ==================================
void DiskEngine::indicateIOBeginStatus()
{
    //Nothing, may be a LED indicator status
}

void DiskEngine::indicateIOEndStatus()
{
    //Nothing, may be a LED indicator status
}

void DiskEngine::indicateIOErrorStatus(int err)
{
    //Nothing, may be a LED indicator status

    cerr << "IO ERROR: " << err << endl;
}

DiskEngine & DiskEngine::getInstance()
{
    return (*DiskEngine::_diskEngineInstance);
}

void DiskEngine::setInstance(DiskEngine *diskEngineInstance)
{
    DiskEngine::_diskEngineInstance = diskEngineInstance;
}


void DiskEngine::toString()
{
    cout << "[DiskEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int DiskEngine::getMemSize()
{
    return sizeof((*this));
}

DiskEngine::~DiskEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[DiskEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

DiskEngine::DiskEngine():
CSAObject()
{

}
