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
#define RECV_SPECIAL_1_CODE     (-61)
#define RECV_SPECIAL_2_CODE     (-62)
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
#define WKTYPE_SPECIAL_1        (1003)
#define WKTYPE_SPECIAL_2        (1004)

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

#define CEDILLA_UC_CODE         (-121)
#define CEDILLA_LC_CODE         (-89)
#define ATILDE_LC_CODE          (-93)
#define ATILDE_UC_CODE          (-129)
#define AGRAVE_LC_CODE          (-96)
#define AGRAVE_UC_CODE          (-128)
#define AACUTE_LC_CODE          (-95)
#define AACUTE_UC_CODE          (-127)
#define ACIRC_LC_CODE           (-94)
#define ACIRC_UC_CODE           (-126)
#define AUML_LC_CODE            (-92)
#define AUML_UC_CODE            (-124)
#define ARING_LC_CODE           (-1)
#define ARING_UC_CODE           (-2)
#define EGRAVE_LC_CODE          (-88)
#define EGRAVE_UC_CODE          (-120)
#define EACUTE_LC_CODE          (-87)
#define EACUTE_UC_CODE          (-119)
#define ECIRC_LC_CODE           (-86)
#define ECIRC_UC_CODE           (-118)
#define EUML_LC_CODE            (-85)
#define EUML_UC_CODE            (-117)
#define IGRAVE_LC_CODE          (-84)
#define IGRAVE_UC_CODE          (-116)
#define IACUTE_LC_CODE          (-83)
#define IACUTE_UC_CODE          (-115)
#define ICIRC_LC_CODE           (-82)
#define ICIRC_UC_CODE           (-114)
#define IUML_LC_CODE            (-81)
#define IUML_UC_CODE            (-113)
#define NTILDE_LC_CODE          (-79)
#define NTILDE_UC_CODE          (-111)
#define OGRAVE_LC_CODE          (-78)
#define OGRAVE_UC_CODE          (-110)
#define OACUTE_LC_CODE          (-77)
#define OACUTE_UC_CODE          (-109)
#define OCIRC_LC_CODE           (-76)
#define OCIRC_UC_CODE           (-108)
#define OTILDE_LC_CODE          (-75)
#define OTILDE_UC_CODE          (-107)
#define OUML_LC_CODE            (-74)
#define OUML_UC_CODE            (-106)
#define UGRAVE_LC_CODE          (-71)
#define UGRAVE_UC_CODE          (-103)
#define UACUTE_LC_CODE          (-70)
#define UACUTE_UC_CODE          (-102)
#define UCIRC_LC_CODE           (-69)
#define UCIRC_UC_CODE           (-101)
#define UUML_LC_CODE            (-68)
#define UUML_UC_CODE            (-100)

#define _1RST_CODE              (-71)
#define _2ND_CODE               (-78)
#define _3RD_CODE                (-77)
#define EURO_CODE               (-93)
#define PARA_CODE               (-89)
#define DOTA_CODE               (-86)
#define GRAU_CODE               (-80)


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
        cout <<"Tipo fn" << rawKeyCode << endl;
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
        case DELETE_CODE: return KeyboardEngine::KEY_DEL;
        default:
            return KeyboardEngine::KEY_HOME;
        }
    } else if (rawKeyType == WKTYPE_SPECIAL_1){
        switch (rawKeyCode)
        {
            case CEDILLA_UC_CODE: return KeyboardEngine::KEY_CEDILLA_LC_CODE;
            case CEDILLA_LC_CODE: return KeyboardEngine::KEY_CEDILLA_UC_CODE;
            case ATILDE_LC_CODE: return KeyboardEngine::KEY_ATILDE_LC_CODE;
            case ATILDE_UC_CODE: return KeyboardEngine::KEY_ATILDE_UC_CODE;
            case AGRAVE_LC_CODE: return KeyboardEngine::KEY_AGRAVE_LC_CODE;
            case AGRAVE_UC_CODE: return KeyboardEngine::KEY_AGRAVE_UC_CODE;
            case AACUTE_LC_CODE: return KeyboardEngine::KEY_AACUTE_LC_CODE;
            case AACUTE_UC_CODE: return KeyboardEngine::KEY_AACUTE_UC_CODE;
            case ACIRC_LC_CODE: return KeyboardEngine::KEY_ACIRC_LC_CODE;
            case ACIRC_UC_CODE: return KeyboardEngine::KEY_ACIRC_UC_CODE;
            case AUML_LC_CODE: return KeyboardEngine::KEY_AUML_LC_CODE;
            case AUML_UC_CODE: return KeyboardEngine::KEY_AUML_UC_CODE;
            case ARING_LC_CODE: return KeyboardEngine::KEY_ARING_LC_CODE;
            case ARING_UC_CODE: return KeyboardEngine::KEY_ARING_UC_CODE;
            case EGRAVE_LC_CODE: return KeyboardEngine::KEY_EGRAVE_LC_CODE;
            case EGRAVE_UC_CODE: return KeyboardEngine::KEY_EGRAVE_UC_CODE;
            case EACUTE_LC_CODE: return KeyboardEngine::KEY_EACUTE_LC_CODE;
            case EACUTE_UC_CODE: return KeyboardEngine::KEY_EACUTE_UC_CODE;
            case ECIRC_LC_CODE: return KeyboardEngine::KEY_ECIRC_LC_CODE;
            case ECIRC_UC_CODE: return KeyboardEngine::KEY_ECIRC_UC_CODE;
            case EUML_LC_CODE: return KeyboardEngine::KEY_EUML_LC_CODE;
            case EUML_UC_CODE: return KeyboardEngine::KEY_EUML_UC_CODE;
            case IGRAVE_LC_CODE: return KeyboardEngine::KEY_IGRAVE_LC_CODE;
            case IGRAVE_UC_CODE: return KeyboardEngine::KEY_IGRAVE_UC_CODE;
            case IACUTE_LC_CODE: return KeyboardEngine::KEY_IACUTE_LC_CODE;
            case IACUTE_UC_CODE: return KeyboardEngine::KEY_IACUTE_UC_CODE;
            case ICIRC_LC_CODE: return KeyboardEngine::KEY_ICIRC_LC_CODE;
            case ICIRC_UC_CODE: return KeyboardEngine::KEY_ICIRC_UC_CODE;
            case IUML_LC_CODE: return KeyboardEngine::KEY_IUML_LC_CODE;
            case IUML_UC_CODE: return KeyboardEngine::KEY_IUML_UC_CODE;
            case NTILDE_LC_CODE: return KeyboardEngine::KEY_NTILDE_LC_CODE;
            case NTILDE_UC_CODE: return KeyboardEngine::KEY_NTILDE_UC_CODE;
            case OGRAVE_LC_CODE: return KeyboardEngine::KEY_OGRAVE_LC_CODE;
            case OGRAVE_UC_CODE: return KeyboardEngine::KEY_OGRAVE_UC_CODE;
            case OACUTE_LC_CODE: return KeyboardEngine::KEY_OACUTE_LC_CODE;
            case OACUTE_UC_CODE: return KeyboardEngine::KEY_OACUTE_UC_CODE;
            case OCIRC_LC_CODE: return KeyboardEngine::KEY_OCIRC_LC_CODE;
            case OCIRC_UC_CODE: return KeyboardEngine::KEY_OCIRC_UC_CODE;
            case OTILDE_LC_CODE: return KeyboardEngine::KEY_OTILDE_LC_CODE;
            case OTILDE_UC_CODE: return KeyboardEngine::KEY_OTILDE_UC_CODE;
            case OUML_LC_CODE: return KeyboardEngine::KEY_OUML_LC_CODE;
            case OUML_UC_CODE: return KeyboardEngine::KEY_OUML_UC_CODE;
            case UGRAVE_LC_CODE: return KeyboardEngine::KEY_UGRAVE_LC_CODE;
            case UGRAVE_UC_CODE: return KeyboardEngine::KEY_UGRAVE_UC_CODE;
            case UACUTE_LC_CODE: return KeyboardEngine::KEY_UACUTE_LC_CODE;
            case UACUTE_UC_CODE: return KeyboardEngine::KEY_UACUTE_UC_CODE;
            case UCIRC_LC_CODE: return KeyboardEngine::KEY_UCIRC_LC_CODE;
            case UCIRC_UC_CODE: return KeyboardEngine::KEY_UCIRC_UC_CODE;
            case UUML_LC_CODE: return KeyboardEngine::KEY_UUML_LC_CODE;
            case UUML_UC_CODE: return KeyboardEngine::KEY_UUML_UC_CODE;
            default:
                return KeyboardEngine::KEY_ANY;
        }
    } else if (rawKeyType == WKTYPE_SPECIAL_2){
        switch (rawKeyCode)
        {

            case _1RST_CODE: return KeyboardEngine::KEY_1RST_CODE;
            case _2ND_CODE: return KeyboardEngine::KEY_2ND_CODE;
            case _3RD_CODE: return KeyboardEngine::KEY_3RD_CODE;
            case EURO_CODE: return KeyboardEngine::KEY_EURO_CODE;
            case PARA_CODE: return KeyboardEngine::KEY_PARA_CODE;
            case DOTA_CODE: return KeyboardEngine::KEY_DOTA_CODE;
            case GRAU_CODE: return KeyboardEngine::KEY_GRAU_CODE;
            default:
                return KeyboardEngine::KEY_ANY;

        }
    } else {
        return KeyboardEngine::KEY_ANY;
    }
}

void WinsockKeyboard::loop()
{
    char buf[1];
    char escBuff[3];

    int escCodeCount = 0;
    int escBuffPos = 0;

    while(!isInterruptLoop())
    {
        ZeroMemory(buf, 1);

        int bytesReceived = recv(_clientSocket, buf, 1, 0);
        if (bytesReceived > 0)
        {
            //cout << "Received: number=[" << (int)buf[0] << "] value=[" << buf[0] << "]" << endl;
            //send(clientSocket, buf, 1, 0);

            if(((int)buf[0]) == RECV_SPECIAL_2_CODE)
            {
                //cout << "[SPECIAL BLOCK 2 CODE INITIALIZED]" << endl;
                ZeroMemory(buf, 1);
                bytesReceived = recv(_clientSocket, buf, 1, 0);
                if (bytesReceived > 0) {
                    switch ((int)buf[0])
                    {
                     case _1RST_CODE:
                     case _2ND_CODE:
                     case _3RD_CODE:
                     case EURO_CODE:
                     case PARA_CODE:
                     case DOTA_CODE:
                     case GRAU_CODE:
                        pressKey(parseRawKeycode(WKTYPE_SPECIAL_2,(int)buf[0]),'\0');
                        break;
                     default:
                        break;
                    }
                }

            } else if(((int)buf[0]) == RECV_SPECIAL_1_CODE) {

                //cout << "[SPECIAL BLOCK 1 CODE INITIALIZED]" << endl;
                ZeroMemory(buf, 1);
                bytesReceived = recv(_clientSocket, buf, 1, 0);
                if (bytesReceived > 0) {
                    switch ((int)buf[0])
                    {
                        case CEDILLA_UC_CODE:
                        case CEDILLA_LC_CODE:
                        case ATILDE_LC_CODE:
                        case ATILDE_UC_CODE:
                        case AGRAVE_LC_CODE:
                        case AGRAVE_UC_CODE:
                        case AACUTE_LC_CODE:
                        case AACUTE_UC_CODE:
                        case ACIRC_LC_CODE:
                        case ACIRC_UC_CODE:
                        case AUML_LC_CODE:
                        case AUML_UC_CODE:
                        case ARING_LC_CODE:
                        case ARING_UC_CODE:
                        case EGRAVE_LC_CODE:
                        case EGRAVE_UC_CODE:
                        case EACUTE_LC_CODE:
                        case EACUTE_UC_CODE:
                        case ECIRC_LC_CODE:
                        case ECIRC_UC_CODE:
                        case EUML_LC_CODE:
                        case EUML_UC_CODE:
                        case IGRAVE_LC_CODE:
                        case IGRAVE_UC_CODE:
                        case IACUTE_LC_CODE:
                        case IACUTE_UC_CODE:
                        case ICIRC_LC_CODE:
                        case ICIRC_UC_CODE:
                        case IUML_LC_CODE:
                        case IUML_UC_CODE:
                        case NTILDE_LC_CODE:
                        case NTILDE_UC_CODE:
                        case OGRAVE_LC_CODE:
                        case OGRAVE_UC_CODE:
                        case OACUTE_LC_CODE:
                        case OACUTE_UC_CODE:
                        case OCIRC_LC_CODE:
                        case OCIRC_UC_CODE:
                        case OTILDE_LC_CODE:
                        case OTILDE_UC_CODE:
                        case OUML_LC_CODE:
                        case OUML_UC_CODE:
                        case UGRAVE_LC_CODE:
                        case UGRAVE_UC_CODE:
                        case UACUTE_LC_CODE:
                        case UACUTE_UC_CODE:
                        case UCIRC_LC_CODE:
                        case UCIRC_UC_CODE:
                        case UUML_LC_CODE:
                        case UUML_UC_CODE:
                            pressKey(parseRawKeycode(WKTYPE_SPECIAL_1,(int)buf[0]), '\0');
                        default:
                            break;
                    }
                }

            } else if(escCodeCount == 0 && ((int)buf[0]) == RECV_ESC_CODE) {
                escCodeCount ++;
                escBuffPos = 0;
            } else if(escCodeCount > 0 && (((int)buf[0]) == RECV_ESC_CODE)) {
                escCodeCount = 0;
                escBuffPos = 0;
                escBuff[0] = 0;
                escBuff[1] = 0;
                escBuff[2] = 0;
                pressKey(KeyboardEngine::KEY_ESCAPE, '\0');
            } else if (escCodeCount == 1 && (((int)buf[0]) == RECV_BEGIN_ESC_CODE)) {
                //cout << "[ESCAPE CODE INITIALIZED]" << endl;
                escCodeCount ++;
            } else if (escCodeCount == 1 && (((int)buf[0]) != RECV_BEGIN_ESC_CODE)) {
                //cout << "[ESCAPE CODE ABORTED]" << endl;
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
                                    //cout << "extra keys code = [" << keyEscCode << "]" << endl;
                                    pressKey(parseRawKeycode(WKTYPE_EXTRA,keyEscCode), '\0');
                                } else {
                                    //cout << "fn key code = [" << keyEscCode << "]" << endl;
                                    pressKey(parseRawKeycode(WKTYPE_FN,keyEscCode), '\0');
                                }
                                escBuffPos = 0;
                                escCodeCount = 0;
                                escBuff[0] = 0;
                                escBuff[1] = 0;
                                escBuff[2] = 0;
                            }
                        } else {
                            if (escBuffPos == 0) {
                                //cout << "arrow key code = [" << (int)buf[0] << "]" << endl;
                                pressKey(parseRawKeycode(WKTYPE_ARROWS,(int)buf[0]), '\0');
                                escBuffPos = 0;
                                escCodeCount = 0;
                                escBuff[0] = 0;
                                escBuff[1] = 0;
                                escBuff[2] = 0;
                            }
                        }
                }
            } else {
               pressKey(KeyboardEngine::KEY_ANY, buf[0]);
            }

        } else {
            cout << "[ NOP ]" << endl;
        }
    }

    setInterruptLoop(false);

}

void WinsockKeyboard::destroy()
{
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


