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
// WINSOCK
#include <winsock2.h>
#define NI_MAXHOST (1024)
#define NI_MAXSERV (1024)

#define RECV_ESC_CODE           (27)
#define RECV_BEGIN_ESC_CODE     (91)
#define RECV_OPT_END_ESC_CODE   (126)
#define RECV_1_CODE             (49)
#define RECV_2_CODE             (50)
#define RECV_3_CODE             (51)
#define RECV_4_CODE             (52)
#define RECV_5_CODE             (53)
#define RECV_6_CODE             (54)
#define RECV_7_CODE             (55)
#define RECV_8_CODE             (56)
#define RECV_9_CODE             (57)
#define RECV_0_CODE             (48)

#define WKTYPE_FN               (1000)
#define WKTYPE_EXTRA            (1001)
#define WKTYPE_ARROWS           (1002)

#define F1_CODE                 (11)
#define F2_CODE                 (12)
#define F3_CODE                 (13)
#define F4_CODE                 (14)
#define F5_CODE                 (15)
#define F6_CODE                 (17)
#define F7_CODE                 (18)
#define F8_CODE                 (19)
#define F9_CODE                 (20)
#define F10_CODE                (21)
#define F11_CODE                (23)
#define F12_CODE                (24)

#define INS_CODE                (2)
#define HOME_CODE               (1)
#define PGUP_CODE               (5)
#define DELETE_CODE             (3)
#define END_CODE                (4)
#define PGDN_CODE               (6)

#define UP_CODE                 (65)
#define DN_CODE                 (66)
#define LEFT_CODE               (68)
#define RIGHT_CODE              (67)

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <iomanip>
using std::setw;

#include "winsock_keyboard.hpp"
#include "app_globals.hpp"


void WinsockKeyboard::setup()
{
    //initialize winsock
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &_wsData);
    if (wsOk != 0)
    {
        cerr << "Error on startup socket" << endl;
        return;
    }

    //create a sockert
    _listenning = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenning == INVALID_SOCKET)
    {
        cerr << "Error on listenning socket" << endl;
        return;
    }

    //bind the ip addr to a socket
    _hint.sin_family = AF_INET;
    _hint.sin_port = htons(_tcpPort);
    _hint.sin_addr.S_un.S_addr = INADDR_ANY; //0.0.0.0

    bind(_listenning, (sockaddr *)&_hint, sizeof(_hint));

    //tell winsock the socket is for listenning
    listen(_listenning, SOMAXCONN); //All possible connections

    //wait for connection
    int clientSize = sizeof(_client);

    _clientSocket = accept(_listenning, (sockaddr*)&_client, &clientSize);
    if (_clientSocket == INVALID_SOCKET)
    {
         cerr << "Invalid socket for client" << endl;
        return;
    }

    char host[NI_MAXHOST]; //Client´s host name
    char service[NI_MAXHOST]; //Service connected in

    ZeroMemory(host, NI_MAXHOST); //same as memset(host, 0, NI_MAX_HOST);
    ZeroMemory(service, NI_MAXHOST);

    //close the sock
    closesocket(_listenning);

}

int WinsockKeyboard::parseRawKeycode(int rawKeyType, int rawKeyCode)
{
    if (rawKeyType == WKTYPE_FN)
    {
        switch(rawKeyCode)
        {
        case F1_CODE: return KeyboardEngine::KEY_F1;
        case F2_CODE: return KeyboardEngine::KEY_F2;
        case F3_CODE: return KeyboardEngine::KEY_F3;
        case F4_CODE: return KeyboardEngine::KEY_F4;
        case F5_CODE: return KeyboardEngine::KEY_F5;
        case F6_CODE: return KeyboardEngine::KEY_F6;
        case F7_CODE: return KeyboardEngine::KEY_F7;
        case F8_CODE: return KeyboardEngine::KEY_F8;
        case F9_CODE: return KeyboardEngine::KEY_F9;
        case F10_CODE: return KeyboardEngine::KEY_F10;
        case F11_CODE: return KeyboardEngine::KEY_F11;
        case F12_CODE: return KeyboardEngine::KEY_F12;
        default:
            return KeyboardEngine::KEY_F1;
        }
    } else if (rawKeyType == WKTYPE_ARROWS){
        switch(rawKeyCode)
        {
        case UP_CODE:    return KeyboardEngine::KEY_UP;
        case DN_CODE:    return KeyboardEngine::KEY_DOWN;
        case LEFT_CODE:  return KeyboardEngine::KEY_LEFT;
        case RIGHT_CODE: return KeyboardEngine::KEY_RIGHT;
        default:
            return KeyboardEngine::KEY_SPACE;
        }
    } else if (rawKeyType == WKTYPE_EXTRA){
        switch(rawKeyCode)
        {
        case INS_CODE:    return KeyboardEngine::KEY_INS;
        case HOME_CODE:   return KeyboardEngine::KEY_HOME;
        case PGUP_CODE:   return KeyboardEngine::KEY_PGUP;
        case END_CODE:    return KeyboardEngine::KEY_END;
        case DELETE_CODE: Return KeyboardEngine::KEY_DEL;
        default:
            return KeyboardEngine::KEY_HOME;
        }
    }
}

void WinsockKeyboard::loop()
{
    char buf[1];
    char escBuff[2];

    int escCodeCount = 0;
    int escBuffPos = 0;

    while(isInterruptLoop())
    {
        ZeroMemory(buf, 1);

        int bytesReceived = recv(_clientSocket, buf, 1, 0);
        if (bytesReceived > 0)
        {
            cout << "Received: number=[" << (int)buf[0] << "] value=[" << buf[0] << "]" << endl;
            //send(clientSocket, buf, 1, 0);

            if(((int)buf[0]) == RECV_ESC_CODE)
            {
                escCodeCount ++;
                escBuffPos = 0;
            } else if (escCodeCount == 1 && (((int)buf[0]) == RECV_BEGIN_ESC_CODE)) {
                cout << "[ESCAPE CODE INITIALIZED]" << endl;
                escCodeCount ++;
            } else if (escCodeCount == 1 && (((int)buf[0]) != RECV_BEGIN_ESC_CODE)) {
                cout << "[ESCAPE CODE ABORTED]" << endl;
                escBuffPos = 0;
                escCodeCount = 0;
            } else if (escCodeCount == 2) {
                switch(((int)buf[0])){
                case RECV_1_CODE:
                    case RECV_2_CODE:
                    case RECV_3_CODE:
                    case RECV_4_CODE:
                    case RECV_5_CODE:
                    case RECV_6_CODE:
                    case RECV_7_CODE:
                    case RECV_8_CODE:
                    case RECV_9_CODE:
                    case RECV_0_CODE:
                        escBuff[escBuffPos] = buf[0];
                        escBuffPos++;
                    default:
                        if (((int)buf[0]) == RECV_OPT_END_ESC_CODE) {
                            if(escBuffPos > 0)
                            {
                                int keyEscCode = atoi(escBuff);
                                if (keyEscCode >= 1 && keyEscCode <= 6)
                                {
                                    cout << "extra keys code = [" << keyEscCode << "]" << endl;
                                } else {
                                    cout << "fn key code = [" << atoi(escBuff) << "]" << endl;
                                }
                                escBuffPos = 0;
                                escCodeCount = 0;
                                escBuff[0] = 0;
                                escBuff[1] = 0;
                                escBuff[2] = 0;
                            }
                        } else {
                            if (escBuffPos == 0) {
                                cout << "arrow key code = [" << (int)buf[0] << "]" << endl;
                                    escBuffPos = 0;
                                    escCodeCount = 0;
                                    escBuff[0] = 0;
                                    escBuff[1] = 0;
                                    escBuff[2] = 0;
                            }
                        }
                }
            }



        } else {
            cout << "[ NOP ]" << endl;
        }
    }

    closesocket(_clientSocket);

    //shutdown winsock
    WSACleanup();

}

void WinsockKeyboard::toString()
{
    cout << "[WinsockKeyboard] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
        << endl;
}

int WinsockKeyboard::getMemSize()
{
    return sizeof((*this));
}

WinsockKeyboard::~WinsockKeyboard()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[WinsockKeyboard] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

WinsockKeyboard::WinsockKeyboard(int tcpPort):
KeyboardEngine(),
_tcpPort(tcpPort)
{

}


