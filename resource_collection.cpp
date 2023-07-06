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

#include "resource_collection.hpp"
#include "app_globals.hpp"

ResourceCollection * ResourceCollection::_me = 0;


UtilsEngine * ResourceCollection::getUtils()
{
    return _utilsEnginePtr;
}

VideoEngine * ResourceCollection::getVideoEngine()
{
    return _videoEnginePtr;
}

TextViewEngine * ResourceCollection::getTextViewEngine()
{
    return _textViewEnginePtr;
}

SplashBoxEngine * ResourceCollection::getSplashBoxEngine()
{
    return _splashBoxEnginePtr;
}

MsgBoxEngine * ResourceCollection::getMsgBoxEngine()
{
    return _msgBoxEnginePtr;
}

MenuEngine * ResourceCollection::getMenuEngine()
{
    return _menuEnginePtr;
}

KeyboardEngine * ResourceCollection::getKeyboardEngine()
{
    return _keyboardEnginePtr;
}

InputBoxEngine * ResourceCollection::getInputBoxEngine()
{
    return _inputBoxEnginePtr;
}

DiskEngine * ResourceCollection::getDiskEngine()
{
    return _diskEnginePtr;
}


void ResourceCollection::setVideoEngine(VideoEngine * videoEngine)
{
    _videoEnginePtr = videoEngine;
}

void ResourceCollection::setTextViewEngine(TextViewEngine * textViewEngine)
{
    _textViewEnginePtr = textViewEngine;
}

void ResourceCollection::setSplashBoxEngine(SplashBoxEngine * splashBoxEngine)
{
    _splashBoxEnginePtr = splashBoxEngine;
}

void ResourceCollection::setMsgBoxEngine(MsgBoxEngine * msgBoxEngine)
{
    _msgBoxEnginePtr = msgBoxEngine;
}

void ResourceCollection::setMenuEngine(MenuEngine * menuEngine)
{
    _menuEnginePtr = menuEngine;
}

void ResourceCollection::setKeyboardEngine(KeyboardEngine * keyboardEngine)
{
    _keyboardEnginePtr = keyboardEngine;
}

void ResourceCollection::setInputBoxEngine(InputBoxEngine * inputBoxEngine)
{
    _inputBoxEnginePtr = inputBoxEngine;
}

void ResourceCollection::setDiskEngine(DiskEngine * diskEngine)
{
    _diskEnginePtr = diskEngine;
}


void ResourceCollection::setUtilsEngine(UtilsEngine * utilsEngine)
{
    _utilsEnginePtr = utilsEngine;
}

void ResourceCollection::toString()
{
    cout << "[ResourceCollection] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int ResourceCollection::getMemSize()
{
    return sizeof((*this));
}

ResourceCollection::~ResourceCollection()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[ResourceCollection] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

ResourceCollection& ResourceCollection::getInstance()
{
    if (ResourceCollection::_me == 0)
    {
        ResourceCollection::_me = new ResourceCollection();
    }
    return (*ResourceCollection::_me);
}


ResourceCollection::ResourceCollection():
CSAObject(),
_videoEnginePtr(0),
_textViewEnginePtr(0),
_splashBoxEnginePtr(0),
_msgBoxEnginePtr(0),
_menuEnginePtr(0),
_keyboardEnginePtr(0),
_inputBoxEnginePtr(0),
_diskEnginePtr(0),
_utilsEnginePtr(0)
{

}

