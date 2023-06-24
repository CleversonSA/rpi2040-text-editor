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
#ifndef SOCKETKEYBOARD
#define SOCKETKEYBOARD

#include <winsock2.h>
#define NI_MAXHOST (1024)
#define NI_MAXSERV (1024)

#include "../app_globals.hpp"
#include "../engine/keyboard_engine.hpp"

/*
    TCP Socket keyboard implementation for Windows. You could use Putty with a no LF to send data.
*/
class WinsockKeyboard: public KeyboardEngine
{
    public:

        WinsockKeyboard(int);
        ~WinsockKeyboard();

        virtual void setup();
        virtual void loop();
        virtual void destroy();

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();

        virtual int parseRawKeycode(int, int);

    private:

        WSADATA     _wsData;
        SOCKET      _listenning;
        sockaddr_in _hint;
        sockaddr_in _client;
        SOCKET      _clientSocket;
        int         _tcpPort = 9000;


};

#endif // DOCUMENT



