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
#ifndef TEXTRENDERENGINEKEYBOARDCALLBACK
#define TEXTRENDERENGINEKEYBOARDCALLBACK

#include "app_globals.hpp"
#include "csa_object.hpp"
#include "engine/video_engine.hpp"
#include "keyboard/keyboard_callback.hpp"
#include "core/text_render_engine.hpp"

/*
  Handle the callback of a keyboard completition for core editor
*/
class TextRenderEngineKeyboardCallback : public KeyboardCallback
{
    public:

        static int _ESCAPE_PRESSES_COUNT;
        static int _LALT_PRESSES_COUNT;

        ~TextRenderEngineKeyboardCallback();
        TextRenderEngineKeyboardCallback();

        void setVideoEngine(VideoEngine *);
        VideoEngine * getVideoEngine();
        void setTextEngine(TextRenderEngine *);
        TextRenderEngine * getTextEngine();

        virtual bool execute(const int, const char);

        virtual void toString();
        virtual int getMemSize();

    private:

        VideoEngine *_videoEngine;
        TextRenderEngine *_textEngine;
};

#endif // DOCCHARACTER






