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
#ifndef ABOUTMENU
#define ABOUTMENU

#include "../csa_object.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/video_engine.hpp"
#include "../engine/menu_engine.hpp"

/*
  Show about info of the System
*/
class About : public CSAObject
{
public:

    About();
    ~About();

    void run();

    virtual void toString(); // Yes, you know, Java feelings rs
    virtual int getMemSize();

private:


};

#endif // DOCCHARACTER
