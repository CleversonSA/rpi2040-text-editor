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
#ifndef INPUTBOXENGINE
#define INPUTBOXENGINE

#include "widget_engine.hpp"
#include "widget_callback.hpp"
#include "video_engine.hpp"
#include "keyboard_engine.hpp"
/*
    Abstract class for InputBox widget
*/
class InputBoxEngine: public WidgetEngine
{
    public:
        static const int CANCEL_TRIGGERED = 60000;
        static const int OK_TRIGGERED = 60500;
        static const int DISPLAY_CONTEXT_ID = 16001;

        InputBoxEngine();
        ~InputBoxEngine();

        InputBoxEngine & setTitle(const char[]);
        char * getTitle() const;
        InputBoxEngine & setMessage(const char[]);
        char * getMessage() const;
        InputBoxEngine & setCallback(WidgetCallback *);
        InputBoxEngine & setInputAction (const int);
        int getInputAction() const;
        InputBoxEngine & setMaxInputSize (const int);
        int getMaxInputSize() const;
        InputBoxEngine & setUserInput(char *);
        char * getUserInput() const;

        InputBoxEngine & type(const char[]);
        InputBoxEngine & type(const char);
        InputBoxEngine & triggerBackspace();
        InputBoxEngine & clearInput();
        InputBoxEngine & triggerEnter();
        InputBoxEngine & triggerESC();


        InputBoxEngine & reset();

        virtual InputBoxEngine & render() = 0;

        virtual void run(VideoEngine *, KeyboardEngine *);
        virtual int getResultIntValue();
        virtual char * getResultCharValue1();

    private:

        char * _title;
        char * _message;
        char * _userInput;
        int _inputAction;
        int _maxInputSize;
        WidgetCallback* _widgetCallback;
};

#endif // DOCUMENT


