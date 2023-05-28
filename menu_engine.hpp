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
#ifndef MENUENGINE
#define MENUENGINE

#include "widget_engine.hpp"
#include "app_globals.hpp"

/*
    Abstract class for Menu widget
*/
class MenuEngine: public WidgetEngine
{
    public:
        MenuEngine();
        ~MenuEngine();

        MenuEngine & setTitle(const char []);
        char * getTitle() const;
        MenuEngine & setCallbackfn(void (*fn)(char *, char *));
        MenuEngine & parseMenuString(char *);
        int getMenuItemCount() const;
        int getMenuItemPos() const;
        char * getSelectedMenuItemLabel() const;
        char * getSelectedMenuItemValue() const;
        char * getMenuItemLabel(const int) const;
        char * getMenuItemValue(const int) const;
        char ** getMenuItems();
        MenuEngine & reset();
        MenuEngine & cursorMoveUp();
        MenuEngine & cursorMoveDown();
        MenuEngine & selectItem();

        virtual MenuEngine & render() = 0;

    private:

        char * parseMenuItem(char *);
        void setMenuItemCount(const int);
        void setMenuItemPos(const int);
        void setMenuItems(char * [], int = AppGlobals::MAX_MENU_ITEMS_COUNT);
        char * _menuItems[AppGlobals::MAX_MENU_ITEMS_COUNT];
        int _menuItemPos;
        int _menuItemCount;
        char * _title;
        void (*_callbackfn)(char *, char *);
};

#endif // DOCUMENT

