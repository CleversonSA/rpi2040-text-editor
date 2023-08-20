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

#include "line_zoom.hpp"
#include "../resource_collection.hpp"
#include "../core_collection.hpp"
#include "line_zoom_keyboard_callback.hpp"

void LineZoom::run()
{

    Document *document = CoreCollection::getInstance().getCurrentDocument();
    TextRenderEngine *textRenderEngine = CoreCollection::getInstance().getTextRenderEngine();
    LineZoomKeyboardCallback *cb = new LineZoomKeyboardCallback(this);

    VideoEngine *video =  ResourceCollection::getInstance().getVideoEngine();
    KeyboardEngine *keyboard = ResourceCollection::getInstance().getKeyboardEngine();

    char titleStr[16];
    char lineContent[4096];
    char *strLineContent = (*textRenderEngine).renderLineToStr((*document).getCurrentRowPtr());


    titleStr[0] = '\0';
    lineContent[0] = '\0';

    int docRow = (*document).getDocRow();

    sprintf(titleStr, "Line #%d", docRow);

    int p = 0;
    int c = 0;
    int lc = 0;

    int sQtd = strlen(strLineContent);

    while (p < sQtd && (lc < 4096)) {

        if (c > 0 && (c % ((*video).getFrameBuffer()->getMaxCols() - 2) == 0)) {
            c = 0;
            lineContent[lc]='\n';
            lc++;
        }

        lineContent[lc] = strLineContent[p];
        c++;
        lc++;
        p++;
    }
    lineContent[lc] = '\0';

    cout << "Texto Menu=" << lineContent << endl;

    (*ResourceCollection::getInstance().getTextViewEngine())
            .reset()
            .parseViewString(lineContent)
            .setTitle(titleStr)
            .setCallback(cb)
            .render()
            .run(video, keyboard);

}


void LineZoom::toString()
{
    cout << "[LineZoom] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LineZoom::getMemSize()
{
    return sizeof((*this));
}

LineZoom::~LineZoom()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LineZoom] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LineZoom::LineZoom():
        CSAObject()
{

}
