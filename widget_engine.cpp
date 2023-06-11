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

#include "widget_engine.hpp"
#include "app_globals.hpp"


int WidgetEngine::getResultIntValue()
{
    return -1;
}

char * WidgetEngine::getResultCharValue1()
{
    return 0;
}

char * WidgetEngine::getResultCharValue2()
{
    return 0;
}

void WidgetEngine::run(VideoEngine *videoEngine, KeyboardEngine *keyboardEngine)
{

}

WidgetEngine::~WidgetEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[WidgetEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

WidgetEngine::WidgetEngine():
CSAObject()
{

}

