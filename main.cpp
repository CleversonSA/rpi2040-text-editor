
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
#include "keyboard_engine.hpp"

#include "lcd4x20_msgbox.hpp"
#include "lcd4x20_inputbox.hpp"
#include "lcd4x20_splashbox.hpp"
#include "lcd4x20_menu.hpp"
#include "lcd4x20_textview.hpp"

#include "winsock_keyboard.hpp"

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
    WinsockKeyboard winsockkeyboard(9000);
    KeyboardEngine *keyboard = &winsockkeyboard;


    (*keyboard).setup();
    (*keyboard).loop();

    cout << "Inicializado" << endl;

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


