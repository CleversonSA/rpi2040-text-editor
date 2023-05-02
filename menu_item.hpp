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
#ifndef MENUITEM
#define MENUITEM

#include "csa_object.hpp"

/*
    Controls logical menu item.
*/
class MenuItem: public CSAObject
{
    public:
        MenuItem(const char [], const int);
        ~MenuItem();

        void setLabel(const char []);
        char * getLabel() const;
        void setValue(const int);
        int getValue() const;
        void setParentMenuItemPtr (MenuItem *);
        MenuItem * getParentMenuItemPtr() const;

        virtual void handle() = 0;

    private:
        char *_label;
        int _value;

        MenuItem *_parentMenuItemPtr;

};

#endif // DOCUMENT

