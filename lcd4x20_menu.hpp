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
#ifndef LCD4X20MENU
#define LCD4X20MENU

#include "menu_engine.hpp"
#include "framebuffer.hpp"

/*
    LCD 4x20 Implementation for Menu List widget
*/
class LCD4X20Menu: public MenuEngine
{
    public:
        LCD4X20Menu(FrameBuffer *);
        ~LCD4X20Menu();

        void setFrameBuffer(FrameBuffer *);
        FrameBuffer * getFrameBuffer() const;

        virtual MenuEngine & render();

        virtual void toString();
        virtual int getMemSize();

    private:

        FrameBuffer *_framebuffer;

        void fitString(const char *, const int, int = 0);
};

#endif // DOCUMENT


