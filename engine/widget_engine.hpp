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
#ifndef WIDGETENGINE
#define WIDGETENGINE

#include "widget_engine.hpp"
#include "../csa_object.hpp"
#include "video_engine.hpp"
#include "keyboard_engine.hpp"

/*
    Abstract class for widgets (Msgbox, inputbox, menulist, views)
*/
class WidgetEngine: public CSAObject
{
    public:
        WidgetEngine();
        ~WidgetEngine();

        virtual void run(VideoEngine *, KeyboardEngine *);

        virtual int getResultIntValue();
        virtual char * getResultCharValue1();
        virtual char * getResultCharValue2();

    private:

};

#endif // DOCUMENT


