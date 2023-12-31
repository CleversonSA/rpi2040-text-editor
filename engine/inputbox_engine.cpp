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
using std::strncat;

#include "inputbox_engine.hpp"
#include "../app_globals.hpp"
#include "widget_callback.hpp"
#include "video_engine.hpp"
#include "keyboard_engine.hpp"
#include "../keyboard/inputbox_keyboard_callback.hpp"


char * InputBoxEngine::getResultCharValue1()
{
    return getUserInput();
}

int  InputBoxEngine::getResultIntValue()
{
    return getInputAction();
}

int InputBoxEngine::getInputAction() const
{
    return _inputAction;
}

void InputBoxEngine::run(VideoEngine *videoEngine, KeyboardEngine *keyboardEngine)
{
    (*videoEngine).display();

    InputboxKeyboardCallback *kcb = new InputboxKeyboardCallback;

    (*kcb).setVideoEngine(videoEngine);
    (*kcb).setInputboxEngine(this);

    cout << "initialized input" << endl;
    (*keyboardEngine).setup();
    cout << "initialized setup" << endl;
    (*keyboardEngine).setCallback(kcb);
    cout << "initialized call" << endl;
    (*keyboardEngine).loop();

    delete kcb;
}


InputBoxEngine & InputBoxEngine::setTitle(const char title[])
{

    _title = new char[strlen(title) + 1];
    strcpy(_title, title);

    return (*this);
}

char * InputBoxEngine::getTitle() const
{
    return _title;
}

InputBoxEngine & InputBoxEngine::setMessage(const char message[])
{

    cout << "Executou 1" <<endl;
    _message = new char[strlen(message) + 1];
    cout << "Executou 2" <<endl;
    strcpy(_message, message);

    cout << "Executou" <<endl;
    return (*this);
}

char * InputBoxEngine::getMessage() const
{
    return _message;
}

InputBoxEngine & InputBoxEngine::type(const char text[])
{
    if (strlen(text) >= getMaxInputSize())
    {
        return (*this);
    }


    _userInput = new char[strlen(text)];
    strcpy(_userInput, text);
    setMaxInputSize(strlen(text));

    return (*this);
}

InputBoxEngine & InputBoxEngine::type(const char character)
{
    if (strlen(_userInput) + 1 > getMaxInputSize())
    {
        return (*this);
    }

    strncat(_userInput, &character, 1);

    return (*this);

}


InputBoxEngine & InputBoxEngine::triggerBackspace()
{
    int size = strlen(_userInput);

    if (size == 0)
    {
        return (*this);
    }

    char * new_string = new char[size - 1];

    for (int i=0; i< (size - 1); i++)
    {
        new_string[i] = _userInput[i];
    }

    new_string[size - 1] = '\0';

    delete _userInput;

    setUserInput(new_string);

    return (*this);
}

InputBoxEngine & InputBoxEngine::setUserInput(char * userInput)
{
    _userInput = new char[getMaxInputSize()];

    strcpy(_userInput, userInput);
    
    return (*this);
}


char * InputBoxEngine::getUserInput() const
{
    return _userInput;
}


InputBoxEngine & InputBoxEngine::setCallback(WidgetCallback *widgetCallback)
{
    _widgetCallback = widgetCallback;

    return (*this);
}



InputBoxEngine & InputBoxEngine::setMaxInputSize(const int maxInputSize)
{
    _maxInputSize = maxInputSize;

    return (*this);
}


int InputBoxEngine::getMaxInputSize() const
{
    return _maxInputSize;
}


InputBoxEngine & InputBoxEngine::clearInput()
{

    _userInput = new char[getMaxInputSize()];
    _userInput[0]='\0';

    return (*this);
}


InputBoxEngine & InputBoxEngine::reset()
{


    clearInput();
    setInputAction(-1);
    setMaxInputSize(16);

    return (*this);
}

InputBoxEngine & InputBoxEngine::setInputAction(const int inputAction)
{
    _inputAction = inputAction;

    return (*this);
}

InputBoxEngine & InputBoxEngine::triggerEnter()
{
    setInputAction(InputBoxEngine::OK_TRIGGERED);
    (*_widgetCallback).execute(this);

    return (*this);
}

InputBoxEngine & InputBoxEngine::triggerESC()
{
    setUserInput(0);
    setInputAction(InputBoxEngine::CANCEL_TRIGGERED);
    (*_widgetCallback).execute(this);

    return (*this);
}

InputBoxEngine::~InputBoxEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[InputBoxEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

InputBoxEngine::InputBoxEngine():
WidgetEngine(),
_title(0),
_message(0),
_userInput(0),
_inputAction(-1),
_maxInputSize(16)
{
    clearInput();
}


