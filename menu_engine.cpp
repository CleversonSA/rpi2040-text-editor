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
using std::strtok;

#include "menu_engine.hpp"
#include "app_globals.hpp"

MenuEngine & MenuEngine::setTitle(const char title[])
{
    if (_title != 0)
    {
        delete _title;
    }

    _title = new char[strlen(title)];
    strcpy(_title, title);

    return (*this);
}


char * MenuEngine::getTitle() const
{
    return _title;
}


void MenuEngine::setMenuItemCount(const int menuItemCount)
{
    _menuItemCount = menuItemCount;
}

int MenuEngine::getMenuItemCount() const
{
    return (_menuItemCount);
}

void MenuEngine::setMenuItemPos(const int menuItemPos)
{
    _menuItemPos = menuItemPos;
}

int MenuEngine::getMenuItemPos() const
{
    return (_menuItemPos);
}

void MenuEngine::setMenuItems(char * menuItems[], int qtItems)
{
    for (int i =0; i < AppGlobals::MAX_MENU_ITEMS_COUNT;  i++)
    {
        _menuItems[i] = 0;
    }

    for (int i = 0; i < qtItems;  i++)
    {
        _menuItems[i] = menuItems[i];
    }
}

//Menu string format: "NEW_FILE;New File|OPEN_FILE;Open File...|SAVE;Save file|SAVE_AS;Save as"
MenuEngine & MenuEngine::parseMenuString(char * menuString)
{
    char *menuStringCpy = new char[strlen(menuString)+1];
    char *itemPtr[AppGlobals::MAX_MENU_ITEMS_COUNT];

    int menuItemPos = 0;
    int menuItemCount = 0;

    // So I think this will create a memory leak, since everytime this command is called
    // a new string is created. But, I think strtok will just assign the string tokens
    // to each pointer. To test it, call parseMenuString so many times until a memory
    // crash o.O
    strcpy(menuStringCpy, menuString);
    char *ptr = strtok(menuStringCpy, AppGlobals::MENU_ITEM_DELIM);

	while(ptr != 0)
	{
        itemPtr[menuItemPos] = ptr;

		ptr = strtok(0, AppGlobals::MENU_ITEM_DELIM);

		menuItemPos++;
        menuItemCount++;
	}

    setMenuItems(itemPtr, menuItemCount);
    setMenuItemCount(menuItemCount);

    return (*this);
}


char ** MenuEngine::getMenuItems()
{
    return _menuItems;
}


char * MenuEngine::getSelectedMenuItemValue() const
{
    return getMenuItemValue(getMenuItemPos());
}


char * MenuEngine::getMenuItemValue(const int menuItemPos) const
{
    if (_menuItems[menuItemPos] == 0)
    {
        char *charEmpty = new char[2];
        strcpy(charEmpty, " ");

        return charEmpty;
    }


    char *itemDetailPtr = 0;
    char *menuItemCpy = new char[strlen(_menuItems[menuItemPos])+1];
    strcpy(menuItemCpy, _menuItems[menuItemPos]);


	itemDetailPtr = strtok(menuItemCpy, AppGlobals::MENU_ITEM_DETAIL_DELIM);

    return itemDetailPtr;
}


char * MenuEngine::getSelectedMenuItemLabel() const
{
    return getMenuItemLabel(getMenuItemPos());
}


char * MenuEngine::getMenuItemLabel(const int menuItemPos) const
{

    if (_menuItems[menuItemPos] == 0)
    {
        char *charEmpty = new char[2];
        strcpy(charEmpty, " ");

        return charEmpty;
    }


    char *itemDetailPtr = 0;
    char *menuItemCpy = new char[strlen(_menuItems[menuItemPos])+1];
    strcpy(menuItemCpy, _menuItems[menuItemPos]);


	itemDetailPtr = strtok(menuItemCpy, AppGlobals::MENU_ITEM_DETAIL_DELIM);
    itemDetailPtr = strtok(0, AppGlobals::MENU_ITEM_DETAIL_DELIM);

    return itemDetailPtr;
}


MenuEngine & MenuEngine::cursorMoveDown()
{
    setMenuItemPos(getMenuItemPos() + 1);

    if (getMenuItemPos() > getMenuItemCount() - 1)
    {
        setMenuItemPos(0);
    }

    return (*this);
}

MenuEngine & MenuEngine::cursorMoveUp()
{
    setMenuItemPos(getMenuItemPos() - 1);

    if (getMenuItemPos() < 0)
    {
        setMenuItemPos(getMenuItemCount() - 1);
    }

    return (*this);
}

MenuEngine & MenuEngine::selectItem()
{
    (*_callbackfn)(getSelectedMenuItemValue(), getSelectedMenuItemLabel());
    return (*this);
}

MenuEngine & MenuEngine::setCallbackfn(void (*fn)(char *, char *))
{
    _callbackfn = fn;

    return (*this);
}

MenuEngine & MenuEngine::reset()
{

    _menuItems[AppGlobals::MAX_MENU_ITEMS_COUNT];

    for (int i = 0; i<AppGlobals::MAX_MENU_ITEMS_COUNT; i++)
    {
        _menuItems[i] = 0;
    }

    setMenuItemCount(0);
    setMenuItemPos(0);
    _callbackfn = 0;

    return (*this);
}


MenuEngine::~MenuEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MenuEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MenuEngine::MenuEngine():
WidgetEngine(),
_menuItemPos(0)
{

}


