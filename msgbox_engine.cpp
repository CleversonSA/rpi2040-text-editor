
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

MsgBoxEngine & MsgBoxEngine::setSelectedButton(const int selectedButton)
{
    _selectedButton = selectedButton;

    return (*this);
}

int MsgBoxEngine::getSelectedButton() const
{
    return _selectedButton;
}

MsgBoxEngine & MsgBoxEngine::setBtnCount(const int btnCount)
{
    _btnCount = btnCount;

    return (*this);
}

int MsgBoxEngine::getBtnCount() const
{
    return _btnCount;
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


MsgBoxEngine & MsgBoxEngine::setCallbackfn(void (*fn)(int))
{
    _callbackfn = fn;

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::setButtonType(const int btnType)
{
    if (_buttonsPtr != 0)
    {
        delete _buttonsPtr;
    }

    switch(btnType)
    {
    case (MsgBoxEngine::YESNO_BUTTON):
        _buttonsPtr = new int [2];
        (*_buttonsPtr) = BTN_YES;
        (*_buttonsPtr++) = BTN_NO;
        _buttonsPtr--;
        setBtnCount(2);
        break;

    case (MsgBoxEngine::YESNOCANCEL_BUTTON):
        _buttonsPtr = new int [3];
        (*_buttonsPtr) = MsgBoxEngine::BTN_YES;
        (*_buttonsPtr++) = MsgBoxEngine::BTN_NO;
        (*_buttonsPtr++) = MsgBoxEngine::BTN_CANCEL;
        _buttonsPtr = _buttonsPtr - 2;
        setBtnCount(3);
        break;

    case (MsgBoxEngine::OKCANCEL_BUTTON):
        _buttonsPtr = new int [2];
        (*_buttonsPtr) = MsgBoxEngine::BTN_OK;
        (*_buttonsPtr++) = MsgBoxEngine::BTN_CANCEL;
        _buttonsPtr = _buttonsPtr - 1;
        setBtnCount(2);
        break;

    default:
        _buttonsPtr = new int [1];
        (*_buttonsPtr) = MsgBoxEngine::BTN_OK;
        setBtnCount(1);
        break;
    }

    setSelectedButton(-1);

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
    if (_buttonsPtr != 0)
    {
        delete _buttonsPtr;
    }

    if (_title != 0)
    {
        delete _title;
    }

    if (_message != 0)
    {
        delete _message;
    }

    setSelectedButton(0);
    setBtnCount(0);
    _callbackfn = 0;

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::cursorMoveNextButton()
{
    setSelectedButton(getSelectedButton() + 1);
    if (getSelectedButton() > getBtnCount())
    {
        setSelectedButton(0);
    }

    render();

    return (*this);
}

MsgBoxEngine & MsgBoxEngine::cursorMovePreviousButton()
{
    setSelectedButton(getSelectedButton() - 1);
    if (getSelectedButton() < 0)
    {
        setSelectedButton(getBtnCount() - 1);
    }

    render();

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
_selectedButton(0),
_btnCount(0),
_buttonsPtr(0),
_title(0),
_message(0)
{

}

