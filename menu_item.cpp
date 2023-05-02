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

#include "menu_item.hpp"
#include "app_globals.hpp"

void MenuItem::setLabel(const char label[])
{
    _label = new char[strlen(label)];

    strcpy(_label, label);
}


char * MenuItem::getLabel() const
{
    return _label;
}


void MenuItem::setValue(const int value)
{
    _value = value;
}


int MenuItem::getValue() const
{
    return _value;
}


void MenuItem::setParentMenuItemPtr (MenuItem * menuItem)
{
    _parentMenuItemPtr = menuItem;
}

MenuItem * MenuItem::getParentMenuItemPtr() const
{
    return _parentMenuItemPtr;
}

MenuItem::~MenuItem()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[MenuItem] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

MenuItem::MenuItem(const char label[], const int value):
CSAObject(),
_label({""}),
_value(value),
_parentMenuItemPtr(0)
{
    setLabel(label);
}

