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
#include "save_as_menu_keyboard_callback.hpp"
#include "../engine/msgbox_engine.hpp"
#include "../engine/inputbox_engine.hpp"


void SaveAsKeyboardCallback::setSourceHandler (int sourceHandler)
{
    _sourceHandler = sourceHandler;
}

int SaveAsKeyboardCallback::getSourceHandler() const
{
    return _sourceHandler;
}

void SaveAsKeyboardCallback::execute(WidgetEngine * widgetEngine)
{
    cout << getSourceHandler() << endl;

    switch(getSourceHandler())
    {
        case (SaveAsKeyboardCallback::INPUTBOX_FILENAME):

            switch((*widgetEngine).getResultIntValue())
            {
                case (InputBoxEngine::OK_TRIGGERED):
                    (*_saveAsMenuPtr).setFileNameToSave((*widgetEngine).getResultCharValue1());
                    (*_saveAsMenuPtr).showConfirmOverwite();
                    break;

                case (InputBoxEngine::CANCEL_TRIGGERED):
                default:
                    (*_saveAsMenuPtr).backToDocument();
                    break;
            }
            break;

        case (SaveAsKeyboardCallback::MSGBOX_OVERWRITE):

            switch((*widgetEngine).getResultIntValue())
            {
                case (MsgBoxEngine::BTN_YES):
                    (*_saveAsMenuPtr).save((*_saveAsMenuPtr).getFileNameToSave());
                    break;

                case (MsgBoxEngine::BTN_NO):
                    (*_saveAsMenuPtr).showInputfileName();
                    break;

                case (MsgBoxEngine::BTN_CANCEL):
                default:
                    (*_saveAsMenuPtr).backToDocument();
                    break;
            }
            break;
    }

}


void SaveAsKeyboardCallback::toString()
{
    cout << "[SaveAsKeyboardCallback] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int SaveAsKeyboardCallback::getMemSize()
{
    return sizeof((*this));
}

SaveAsKeyboardCallback::~SaveAsKeyboardCallback()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[SaveAsKeyboardCallback] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

SaveAsKeyboardCallback::SaveAsKeyboardCallback(SaveAsMenu * saveAsMenu):
WidgetCallback(),
_saveAsMenuPtr(saveAsMenu),
_sourceHandler(0)
{

}




