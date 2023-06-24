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
#ifndef RPI2040TEXTENGINE
#define RPI2040TEXTENGINE

#include "../engine/document_engine.hpp"
#include "../document/document.hpp"
#include "../engine/video_engine.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/widget_callback.hpp"

//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"

/*
  Document engine processing for RPI2040 only
*/
class Rpi2040TextEngine : public TextEngine
{
    public:
        Rpi2040TextEngine(Document *, VideoEngine *);
        ~Rpi2040TextEngine();

        virtual void renderColRow(int, int, int);

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();


    private:

        uint LED_PIN;
        uint _ledOn;


};

#endif // DOCCHARACTER




