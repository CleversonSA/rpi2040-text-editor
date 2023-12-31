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
#ifndef OPENFILEMENUKEYBOARDCALLBACK
#define OPENFILEMENUKEYBOARDCALLBACK

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "keyboard/menu_keyboard_callback.hpp"
#include "core/open_file_menu.hpp"

/*
  Handle the callback of a keyboard completition for Open File Menu feature menu
*/
class OpenFileMenuKeyboardCallback : public WidgetCallback
{
public:
    static const int MSGBOX_SAVE_CHANGES = 21300;

    OpenFileMenuKeyboardCallback(OpenFileMenu *);
    ~OpenFileMenuKeyboardCallback();

    virtual void execute(WidgetEngine *);
    void setSourceHandler (int);
    int getSourceHandler() const;

    virtual void toString();
    virtual int getMemSize();

private:

    OpenFileMenu *_openFileMenuPtr;

    int _sourceHandler = 0;

};

#endif // DOCCHARACTER






