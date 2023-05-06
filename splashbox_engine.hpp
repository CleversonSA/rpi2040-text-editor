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
#ifndef SPLASHBOXENGINE
#define SPLASHBOXENGINE

#include "widget_engine.hpp"

/*
    Abstract class for Splashbox widget
*/
class SplashBoxEngine: public WidgetEngine
{
    public:
        static const int NO_ICON = 73600;
        static const int EXCLAMATION_ICON = 73601;
        static const int ERROR_ICON = 73602;
        static const int INFO_ICON = 73603;
        static const int QUESTION_ICON = 73604;

        SplashBoxEngine();
        ~SplashBoxEngine();

        SplashBoxEngine & setTitle(const char[]);
        char * getTitle() const;
        SplashBoxEngine & setMessage(const char[]);
        char * getMessage() const;
        SplashBoxEngine & setCallbackfn(void (*fn)(void));
        SplashBoxEngine & reset();
        SplashBoxEngine & setIconType(const int);
        int getIconType() const;

        SplashBoxEngine & hide();

        virtual SplashBoxEngine & render() = 0;

    private:

        char * _title;
        char * _message;
        int _iconType;
        void (*_callbackfn)(void);
};

#endif // DOCUMENT



