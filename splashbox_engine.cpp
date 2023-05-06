
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

#include "splashbox_engine.hpp"
#include "app_globals.hpp"

SplashBoxEngine & SplashBoxEngine::setTitle(const char title[])
{
    if (_title != 0)
    {
        delete _title;
    }

    _title = new char[strlen(title)];
    strcpy(_title, title);

    return (*this);
}

char * SplashBoxEngine::getTitle() const
{
    return _title;
}

SplashBoxEngine & SplashBoxEngine::setMessage(const char message[])
{
    if (_message != 0)
    {
        delete _message;
    }

    _message = new char[strlen(message)];
    strcpy(_message, message);

    return (*this);
}

char * SplashBoxEngine::getMessage() const
{
    return _message;
}


SplashBoxEngine & SplashBoxEngine::setCallbackfn(void (*fn)(void))
{
    _callbackfn = fn;

    return (*this);
}

SplashBoxEngine & SplashBoxEngine::setIconType(const int iconType)
{
    _iconType = iconType;

    return (*this);
}

int SplashBoxEngine::getIconType() const
{
    return _iconType;
}


SplashBoxEngine & SplashBoxEngine::reset()
{

    if (_title != 0)
    {
        delete _title;
    }

    if (_message != 0)
    {
        delete _message;
    }

    setIconType(SplashBoxEngine::NO_ICON);
    _callbackfn = 0;

    return (*this);
}

SplashBoxEngine & SplashBoxEngine::hide()
{
    _callbackfn();

    return (*this);
}

SplashBoxEngine::~SplashBoxEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[SplashBoxEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

SplashBoxEngine::SplashBoxEngine():
WidgetEngine(),
_title(0),
_message(0),
_iconType(SplashBoxEngine::NO_ICON)
{

}


