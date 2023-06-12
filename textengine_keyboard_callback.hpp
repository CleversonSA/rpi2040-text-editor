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
#ifndef TEXTENGINEKEYBOARDCALLBACK
#define TEXTENGINEKEYBOARDCALLBACK

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "video_engine.hpp"
#include "keyboard_callback.hpp"
#include "text_engine.hpp"

/*
  Handle the callback of a keyboard completition for document editor
*/
class TextEngineKeyboardCallback : public KeyboardCallback
{
    public:

        ~TextEngineKeyboardCallback();
        TextEngineKeyboardCallback();

        void setVideoEngine(VideoEngine *);
        VideoEngine * getVideoEngine();
        void setTextEngine(TextEngine *);
        TextEngine * getTextEngine();

        virtual bool execute(const int, const char);

        virtual void toString();
        virtual int getMemSize();

    private:

        VideoEngine *_videoEngine;
        TextEngine *_textEngine;
};

#endif // DOCCHARACTER





