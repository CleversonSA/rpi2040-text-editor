
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

#include "msgbox_engine.hpp"
#include "app_globals.hpp"

int MsgBoxEngine::getButtonType() const
{
    return _buttonType;
}

MsgBoxEngine & MsgBoxEngine::setSelectedButton(const int selectedButton)
{
    _selectedButton = selectedButton;

    return (*this);
}

int MsgBoxEngine::getSelectedButton() const
{
    return _selectedButton;
}

MsgBoxEngine & MsgBoxEngine::setTitle(const char title[])
{
    if (_title != 0)
    {
        delete _title;
    }

    _title = new char[strlen(title)];
    strcpy(_title, title);

    return (*this);
}

char * MsgBoxEngine::getTitle() const
{
    return _title;
}

MsgBoxEngine & MsgBoxEngine::setMessage(const char message[])
{
    if (_message != 0)
    {
        delete _message;
    }

    _message = new char[strlen(message)];
    strcpy(_message, message);

    return (*this);
}

char * MsgBoxEngine::getMessage() const
{
    return _message;
}


MsgBoxEngine & MsgBoxEngine::setCallbackfn(void (*fn)(const int))
{
    _callbackfn = fn;

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::setIconType(const int iconType)
{
    _iconType = iconType;

    return (*this);
}

int MsgBoxEngine::getIconType() const
{
    return _iconType;
}

MsgBoxEngine & MsgBoxEngine::setButtonType(const int btnType)
{
    switch(btnType)
    {
    case (MsgBoxEngine::YESNO_BUTTON):
        setSelectedButton(MsgBoxEngine::BTN_NO);
        break;

    case (MsgBoxEngine::YESNOCANCEL_BUTTON):
        setSelectedButton(MsgBoxEngine::BTN_CANCEL);
        break;

    case (MsgBoxEngine::OKCANCEL_BUTTON):
        setSelectedButton(MsgBoxEngine::BTN_CANCEL);
        break;

    default:
        setSelectedButton(MsgBoxEngine::BTN_OK);
        break;
    }

    _buttonType = btnType;

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::selectButton()
{
    (*_callbackfn)(getSelectedButton());
    reset();

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::reset()
{

    if (_title != 0)
    {
        delete _title;
    }

    if (_message != 0)
    {
        delete _message;
    }

    setIconType(MsgBoxEngine::NO_ICON);
    setButtonType(MsgBoxEngine::OK_BUTTON);
    _callbackfn = 0;

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::cursorMoveNextButton()
{
    switch(getButtonType())
    {
    case(MsgBoxEngine::OKCANCEL_BUTTON):
        if (getSelectedButton() == MsgBoxEngine::BTN_OK)
        {
            setSelectedButton(MsgBoxEngine::BTN_CANCEL);
        } else {
            setSelectedButton(MsgBoxEngine::BTN_OK);
        }
        break;
    case(MsgBoxEngine::YESNO_BUTTON):
        if (getSelectedButton() == MsgBoxEngine::BTN_YES)
        {
            setSelectedButton(MsgBoxEngine::BTN_NO);
        } else {
            setSelectedButton(MsgBoxEngine::BTN_YES);
        }
        break;
    case(MsgBoxEngine::YESNOCANCEL_BUTTON):
        if (getSelectedButton() == MsgBoxEngine::BTN_YES)
        {
            setSelectedButton(MsgBoxEngine::BTN_NO);
        } else if (getSelectedButton() == MsgBoxEngine::BTN_NO) {
            setSelectedButton(MsgBoxEngine::BTN_CANCEL);
        } else {
            setSelectedButton(MsgBoxEngine::BTN_YES);
        }
        break;
    default:
        setSelectedButton(MsgBoxEngine::BTN_OK);
        break;
    }

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::cursorMovePreviousButton()
{
    switch(getButtonType())
    {
    case(MsgBoxEngine::OKCANCEL_BUTTON):
        if (getSelectedButton() == MsgBoxEngine::BTN_OK)
        {
            setSelectedButton(MsgBoxEngine::BTN_CANCEL);
        } else {
            setSelectedButton(MsgBoxEngine::BTN_OK);
        }
        break;
    case(MsgBoxEngine::YESNO_BUTTON):
        if (getSelectedButton() == MsgBoxEngine::BTN_YES)
        {
            setSelectedButton(MsgBoxEngine::BTN_NO);
        } else {
            setSelectedButton(MsgBoxEngine::BTN_YES);
        }
        break;
    case(MsgBoxEngine::YESNOCANCEL_BUTTON):
        if (getSelectedButton() == MsgBoxEngine::BTN_YES)
        {
            setSelectedButton(MsgBoxEngine::BTN_CANCEL);
        } else if (getSelectedButton() == MsgBoxEngine::BTN_CANCEL) {
            setSelectedButton(MsgBoxEngine::BTN_NO);
        } else {
            setSelectedButton(MsgBoxEngine::BTN_YES);
        }
        break;
    default:
        setSelectedButton(MsgBoxEngine::BTN_OK);
        break;
    }

    return (*this);
}

MsgBoxEngine::~MsgBoxEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MsgBoxEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MsgBoxEngine::MsgBoxEngine():
WidgetEngine(),
_selectedButton(MsgBoxEngine::BTN_OK),
_title(0),
_message(0),
_buttonType(MsgBoxEngine::OK_BUTTON),
_iconType(MsgBoxEngine::NO_ICON)
{

}

