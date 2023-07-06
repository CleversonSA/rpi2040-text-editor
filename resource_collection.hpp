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
#ifndef RESOURCECOLLECTION
#define RESOURCECOLLECTION

#include "csa_object.hpp"
#include "engine/disk_engine.h"
#include "engine/inputbox_engine.hpp"
#include "engine/keyboard_engine.hpp"
#include "engine/menu_engine.hpp"
#include "engine/msgbox_engine.hpp"
#include "engine/splashbox_engine.hpp"
#include "engine/textview_engine.hpp"
#include "engine/video_engine.hpp"
#include "engine/utils_engine.hpp"


/*
  General resource holder to manager singletons and avoid constructor overhead
*/
class ResourceCollection : public CSAObject
{
public:

    ~ResourceCollection();

    static ResourceCollection & getInstance();

    VideoEngine * getVideoEngine();
    TextViewEngine * getTextViewEngine();
    SplashBoxEngine * getSplashBoxEngine();
    MsgBoxEngine * getMsgBoxEngine();
    MenuEngine * getMenuEngine();
    KeyboardEngine * getKeyboardEngine();
    InputBoxEngine * getInputBoxEngine();
    DiskEngine * getDiskEngine();
    UtilsEngine * getUtils();

    void setVideoEngine(VideoEngine *);
    void setTextViewEngine(TextViewEngine *);
    void setSplashBoxEngine(SplashBoxEngine *);
    void setMsgBoxEngine(MsgBoxEngine *);
    void setMenuEngine(MenuEngine *);
    void setKeyboardEngine(KeyboardEngine *);
    void setInputBoxEngine(InputBoxEngine *);
    void setDiskEngine(DiskEngine *);
    void setUtilsEngine(UtilsEngine *);


    virtual void toString(); // Yes, you know, Java feelings rs
    virtual int getMemSize();

private:
    ResourceCollection();

    static ResourceCollection* _me;

    VideoEngine * _videoEnginePtr;
    TextViewEngine * _textViewEnginePtr;
    SplashBoxEngine * _splashBoxEnginePtr;
    MsgBoxEngine * _msgBoxEnginePtr;
    MenuEngine * _menuEnginePtr;
    KeyboardEngine * _keyboardEnginePtr;
    InputBoxEngine * _inputBoxEnginePtr;
    DiskEngine * _diskEnginePtr;
    UtilsEngine * _utilsEnginePtr;


};

#endif // DOCCHARACTER

