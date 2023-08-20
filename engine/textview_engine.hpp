
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
#ifndef TEXTVIEW
#define TEXTVIEW

#include "widget_engine.hpp"
#include "../app_globals.hpp"
#include "menu_engine.hpp"
#include "widget_callback.hpp"
#include "video_engine.hpp"
#include "keyboard_engine.hpp"
#include "widget_callback.hpp"

/*
    Abstract class for Text View Engine
*/
class TextViewEngine: public WidgetEngine
{
    public:
        TextViewEngine(MenuEngine *);
        ~TextViewEngine();

        static const int DISPLAY_CONTEXT_ID = 16007;

        TextViewEngine & setTitle(const char []);
        char * getTitle() const;
        int getViewLinesCount() const;
        int getViewLinePos() const;
        TextViewEngine & parseViewString(char *);
        char ** getTextLines();
        char * getTextLine(const int) const;
        TextViewEngine & reset();
        TextViewEngine & cursorMoveUp();
        TextViewEngine & cursorMoveDown();
        TextViewEngine & closeView();

         TextViewEngine & setCallback(WidgetCallback *);

        virtual TextViewEngine & render() = 0;
        virtual void run(VideoEngine *, KeyboardEngine *);

    private:

        MenuEngine * _menuEngineInstance;
        char * _title;
        WidgetCallback* _widgetCallback;
};

#endif // DOCUMENT


