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
#ifndef NEWFILEMENUKEYBOARDCALLBACK
#define NEWFILEMENUKEYBOARDCALLBACK

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "keyboard/menu_keyboard_callback.hpp"
#include "core/new_file_menu.hpp"

/*
  Handle the callback of a keyboard completition for New File Menu feature menu
*/
class NewFileMenuKeyboardCallback : public WidgetCallback
{
public:

    NewFileMenuKeyboardCallback(NewFileMenu *);
    ~NewFileMenuKeyboardCallback();

    virtual void execute(WidgetEngine *);

    virtual void toString();
    virtual int getMemSize();

private:

    NewFileMenu *_newFileMenuPtr;
};

#endif // DOCCHARACTER






