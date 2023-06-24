
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
#ifndef RPI2040UARTVIDEO
#define RPI2040UARTVIDEO

#include "../app_globals.hpp"
#include "../engine/video_engine.hpp"

/*
    Display the App GUI at RPI UART Serial Console
*/
class Rpi2040UartVideo: public VideoEngine
{
    public:

        Rpi2040UartVideo();
        ~Rpi2040UartVideo();

       virtual VideoEngine & display();

       virtual void toString(); // Yes, you know, Java feelings rs
       virtual int getMemSize();

};

#endif // DOCUMENT



