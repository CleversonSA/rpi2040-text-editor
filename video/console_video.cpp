
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

#include "console_video.hpp"
#include "../engine/video_engine.hpp"
#include "../app_globals.hpp"


VideoEngine & ConsoleVideo::display()
{
    char * screenLine = 0;

    system("cls");
    for (int i=0; i < (*getFrameBuffer()).getMaxRows(); i++)
    {
        screenLine = (*getFrameBuffer()).getScreenRow(i);
        for (int j=0; j < (*getFrameBuffer()).getMaxCols(); j++)
        {
            if ((*screenLine) == '\0')
            {
                cout << " ";
            } else {
                cout << (*screenLine);
            }
            screenLine++;
        }
        cout << endl;
    }
}

void ConsoleVideo::toString()
{
    cout << "[ConsoleVideo] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int ConsoleVideo::getMemSize()
{
    return sizeof((*this));
}


ConsoleVideo::~ConsoleVideo()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[ConsoleVideo] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

ConsoleVideo::ConsoleVideo():
VideoEngine()
{

}



