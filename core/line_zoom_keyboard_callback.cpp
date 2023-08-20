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
#include <cstdio>
using std::sprintf;

#include <cstring>
using std::strcmp;

#include <iostream>
using std::cout;
using std::endl;

#include "../app_globals.hpp"
#include "line_zoom_keyboard_callback.hpp"
#include "../core_collection.hpp"
#include "../resource_collection.hpp"
#include "../core/line_zoom.hpp"

void LineZoomKeyboardCallback::execute(WidgetEngine * widgetEngine)
{
    // HIT ESC

    // FIX-ME: This will cause stack overflow
    (*CoreCollection::getInstance().getTextRenderEngine()).run(
            ResourceCollection::getInstance().getVideoEngine(),
            ResourceCollection::getInstance().getKeyboardEngine()
    );
    return;

}


void LineZoomKeyboardCallback::toString()
{
    cout << "[LineZoomKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int LineZoomKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

LineZoomKeyboardCallback::~LineZoomKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LineZoomKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LineZoomKeyboardCallback::LineZoomKeyboardCallback(LineZoom * lineZoomPtr):
        WidgetCallback(),
        _lineZoomPtr(lineZoomPtr)
{

}




