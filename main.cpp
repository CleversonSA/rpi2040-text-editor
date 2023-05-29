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


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

#include <cstring>
using std::strlen;
using std::strtok;
using std::atoi;

#include "csa_object.hpp"
#include "doc_character.hpp"
#include "doc_row.hpp"
#include "app_globals.hpp"
#include "document.hpp"
#include "framebuffer.hpp"

#include "text_engine.hpp"
#include "msgbox_engine.hpp"
#include "inputbox_engine.hpp"
#include "splashbox_engine.hpp"
#include "menu_engine.hpp"
#include "textview_engine.hpp"

#include "lcd4x20_msgbox.hpp"
#include "lcd4x20_inputbox.hpp"
#include "lcd4x20_splashbox.hpp"
#include "lcd4x20_menu.hpp"
#include "lcd4x20_textview.hpp"

int getMemSize(CSAObject *);
void frameBufferToConsole(FrameBuffer *fb);

int main()
{
    int pausa = 0;

    /*FrameBuffer fb(4,20);
    FrameBuffer fbMsgbox(4,20);
    FrameBuffer fbInputbox(4,20);
    FrameBuffer fbSplashBox(4,20);
    FrameBuffer fbMenu(4,20);
    FrameBuffer fbTextView(4,20);

    LCD4X20MsgBox lcd4x20msgbox(&fbMsgbox);
    LCD4X20InputBox lcd4x20inputbox(&fbInputbox);
    LCD4X20Splashbox lcd4x20splashbox(&fbSplashBox);
    LCD4X20Menu lcd4x20menu(&fbMenu);

    MsgBoxEngine *msgbox = &lcd4x20msgbox;
    InputBoxEngine *inputbox = &lcd4x20inputbox;
    SplashBoxEngine *splashbox = &lcd4x20splashbox;
    MenuEngine *menu = &lcd4x20menu;

    LCD4X20TextView lcd4x20textview(&fbTextView, menu);
    TextViewEngine *textView = &lcd4x20textview;
*/

    cout << "Inicializado" << endl;

    //initialize winsock
    WSADATA wsData;
    WORD ver = MAKEWORD(2, 2);

    int wsOk = WSAStartup(ver, &wsData);
    if (wsOk != 0)
    {
        cerr << "Error winsock" << endl;
        return -1;
    }

    //create a sockert
    SOCKET listenning = socket(AF_INET, SOCK_STREAM, 0);
    if (listenning == INVALID_SOCKET)
    {
        cerr << "Error winsock 2" << endl;
        return -2;
    }

    //bind the ip addr to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(9000);
    hint.sin_addr.S_un.S_addr = INADDR_ANY; //0.0.0.0

    bind(listenning, (sockaddr *)&hint, sizeof(hint));

    //tell winsock the socket is for listenning
    listen(listenning, SOMAXCONN); //All possible connections

    //wait for connection
    sockaddr_in client;
    int clientSize = sizeof(client);

    SOCKET clientSocket = accept(listenning, (sockaddr*)&client, &clientSize);
    if (clientSocket == INVALID_SOCKET)
    {
         cerr << "Invalid socket" << endl;
        return -3;
    }

    char host[NI_MAXHOST]; //Client´s host name
    char service[NI_MAXHOST]; //Service connected in

    ZeroMemory(host, NI_MAXHOST); //same as memset(host, 0, NI_MAX_HOST);
    ZeroMemory(service, NI_MAXHOST);

    /*
    Works only on M$ Visual Studio
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    } else {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }*/

    //close the sock
    closesocket(listenning);

    //while loop
    char buf[1];
    char escBuff[2];

    int escCodeCount = 0;
    int escBuffPos = 0;

    while(true)
    {
        ZeroMemory(buf, 1);

        int bytesReceived = recv(clientSocket, buf, 1, 0);
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

    closesocket(clientSocket);

    //shutdown winsock
    WSACleanup();

	return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}

void frameBufferToConsole(FrameBuffer *fb)
{
    char * screenLine = 0;

    system("cls");
    for (int i=0; i < (*fb).getMaxRows(); i++)
    {
        screenLine = (*fb).getScreenRow(i);
        for (int j=0; j < (*fb).getMaxCols(); j++)
        {
            if ((*screenLine) == '\0')
            {
                cout << " ";
            } else {
                cout << (*screenLine);
            }
            screenLine++;
        }
        cout << endl;
    }
}


