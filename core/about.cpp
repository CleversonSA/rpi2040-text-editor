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

#include <cstring>
using std::strcat;

#include <cstdio>
using std::sprintf;

#include <iomanip>
using std::setw;

#include "about.hpp"
#include "../resource_collection.hpp"
#include "about_keyboard_callback.hpp"

void About::run()
{

    AboutKeyboardCallback *cb = new AboutKeyboardCallback(this);

    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();

    char titleStr[16];
    char lineContent[4096];
    char tmp[100];

    titleStr[0] = '\0';
    lineContent[0] = '\0';
    tmp[0] = '\0';

    uint32_t mfree = AppGlobals::getInstance().getFreeHeap();
    uint32_t mtotal =  AppGlobals::getInstance().getTotalHeap();
    uint32_t mused = mtotal - mfree;

    sprintf(titleStr, "About");
    //                   123456789012344567
    strcat(lineContent, " BARE METAL TEXT\n");
    strcat(lineContent, "     EDITOR\n");
    strcat(lineContent, "----------------\n");
    strcat(lineContent, "Memory info:\n");
    strcat(lineContent, " Used (bytes):\n");
    sprintf(tmp," %u\n", mused );
    strcat(lineContent, tmp);
    strcat(lineContent, " Free (bytes):\n");
    sprintf(tmp," %u\n", mfree );
    strcat(lineContent, tmp);
    strcat(lineContent, " Total (bytes):\n");
    sprintf(tmp," %u\n", mtotal);
    strcat(lineContent, tmp);
    strcat(lineContent, "----------------\n");
    strcat(lineContent, "Author:\n");
    strcat(lineContent, " Cleverson S A\n");
    strcat(lineContent, "Github:\n");
    strcat(lineContent, " CleversonSA\n");
    strcat(lineContent, "I.G.:\n");
    strcat(lineContent, " @pu5tos\n");
    strcat(lineContent, "----------------\n");

    (*ResourceCollection::getInstance().getTextViewEngine())
            .reset()
            .parseViewString(lineContent)
            .setTitle(titleStr)
            .setCallback(cb)
            .render()
            .run(video, keyboard);

}


void About::toString()
{
    cout << "[About] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int About::getMemSize()
{
    return sizeof((*this));
}

About::~About()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[About] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

About::About():
        CSAObject()
{

}
