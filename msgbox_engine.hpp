
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
#ifndef MSGBOXENGINE
#define MSGBOXENGINE

#include "widget_engine.hpp"

/*
    Abstract class for MsgBox widget
*/
class MsgBoxEngine: public WidgetEngine
{
    public:
        static const int NO_ICON = 53600;
        static const int EXCLAMATION_ICON = 53601;
        static const int ERROR_ICON = 53602;
        static const int INFO_ICON = 53603;
        static const int QUESTION_ICON = 53604;

        static const int BTN_OK = 53500;
        static const int BTN_YES = 53501;
        static const int BTN_CANCEL = 53502;
        static const int BTN_NO = 53503;

        static const int YESNO_BUTTON=53000;
        static const int YESNOCANCEL_BUTTON=53001;
        static const int OKCANCEL_BUTTON=53002;
        static const int OK_BUTTON=53003;

        MsgBoxEngine();
        ~MsgBoxEngine();

        MsgBoxEngine & setTitle(const char[]);
        char * getTitle() const;
        MsgBoxEngine & setMessage(const char[]);
        char * getMessage() const;
        MsgBoxEngine & setCallbackfn(void (*fn)(const int));
        MsgBoxEngine & setSelectedButton (const int);
        int getSelectedButton() const;
        MsgBoxEngine & setButtonType(const int);
        int getButtonType() const;
        MsgBoxEngine & selectButton();
        MsgBoxEngine & reset();
        MsgBoxEngine & setIconType(const int);
        int getIconType() const;

        MsgBoxEngine & cursorMoveNextButton();
        MsgBoxEngine & cursorMovePreviousButton();

        virtual MsgBoxEngine & render() = 0;
        virtual void run(VideoEngine *, KeyboardEngine *);

    private:

        char * _title;
        char * _message;
        int _selectedButton;
        int _buttonType;
        int _iconType;
        void (*_callbackfn)(const int);
};

#endif // DOCUMENT


