
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
#ifndef VIDEOENGINE
#define VIDEOENGINE

#include "../app_globals.hpp"
#include "../video/framebuffer.hpp"
#include "../csa_object.hpp"

/*
    Abstract class for display the App GUI. May be Console, Serial, LCD Display, VGA, CRT Terminal
*/
class VideoEngine: public CSAObject
{
    public:

        VideoEngine();
        ~VideoEngine();

        FrameBuffer * getFrameBuffer();
        VideoEngine & setFrameBuffer(FrameBuffer *);

        virtual VideoEngine & reset();

        // The int value is a optional identifier for specific display depending
        // of the app context.
        virtual VideoEngine & display(int = 0) = 0;

    private:

        FrameBuffer * _fb;

};

#endif // DOCUMENT


