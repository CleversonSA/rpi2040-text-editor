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
#ifndef MAINMENUKEYBOARDCALLBACK
#define MAINMENUKEYBOARDCALLBACK

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "keyboard/menu_keyboard_callback.hpp"
#include "core/main_menu.hpp"

/*
  Handle the callback of a keyboard completition for Main Menu
*/
class MainMenuKeyboardCallback : public WidgetCallback
{
public:

    MainMenuKeyboardCallback(MainMenu *);
    ~MainMenuKeyboardCallback();

    virtual void execute(WidgetEngine *);

    virtual void toString();
    virtual int getMemSize();

private:

    MainMenu *_mainMenuPtr;
};

#endif // DOCCHARACTER






