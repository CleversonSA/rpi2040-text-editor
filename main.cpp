
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

#include <cstdio>
using std::sprintf;

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
#include "video_engine.hpp"

#include "lcd4x20_msgbox.hpp"
#include "lcd4x20_inputbox.hpp"
#include "lcd4x20_splashbox.hpp"
#include "lcd4x20_menu.hpp"
#include "lcd4x20_textview.hpp"

#include "console_video.hpp"


#include "VT100_utils.hpp"
#include "rpi2040_uart.hpp"
#include "rpi2040_uart_keyboard.hpp"
#include "rpi2040_uart_video.hpp"

#include "msgbox_sample_callback.hpp"
#include "menu_sample_callback.hpp"
#include "inputbox_sample_callback.hpp"


//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "pico/time.h"

Rpi2040Uart rpi2040uart = Rpi2040Uart::getInstance();

int getMemSize(CSAObject *);
bool onKeyPress(const int keyCode, const char rawKeyChar);
void onMsgBoxReturn(const int btnSelected);


int main()
{
    int pausa = 0;

    /*FrameBuffer fb(4,20);
    */
    FrameBuffer fbMsgbox(4,20);
    FrameBuffer fbMenu(4,20);
    FrameBuffer fbSplashBox(4,20);
    FrameBuffer fbInputbox(4,20);
    FrameBuffer fbTextView(4,20);
    /*

    */
    LCD4X20MsgBox lcd4x20msgbox(&fbMsgbox);
    LCD4X20Menu lcd4x20menu(&fbMenu);
    LCD4X20Splashbox lcd4x20splashbox(&fbSplashBox);
    LCD4X20InputBox lcd4x20inputbox(&fbInputbox);
    /*

    */
    MsgBoxEngine *msgbox = &lcd4x20msgbox;
    MenuEngine *menu = &lcd4x20menu;
    SplashBoxEngine *splashbox = &lcd4x20splashbox;
    InputBoxEngine *inputbox = &lcd4x20inputbox;


    LCD4X20TextView lcd4x20textview(&fbTextView, menu);
    TextViewEngine *textView = &lcd4x20textview;


    rpi2040uart.setup();
    Rpi2040UartKeyboard rpiUartKb = Rpi2040UartKeyboard::getInstance();
    KeyboardEngine *keyboard = &rpiUartKb;

    Rpi2040UartVideo rpi2040UartVideo;
    rpi2040uart.setup();
    VideoEngine *video = &rpi2040UartVideo;

    MsgboxSampleCallback msgcb;
    MenuSampleCallback menucb;
    InputboxSampleCallback inputboxcb;


    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"Inputbox widget will be tested!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    sleep_ms(3000);

    (*video)
        .setFrameBuffer(&fbInputbox);

    (*inputbox)
        .reset()
        .setTitle({"Nome:"})
        .setMessage({"Informe um nome:"})
        .setCallback(&inputboxcb)
        .render()
        .run(video, keyboard);

    sleep_ms(3000);


    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"Menu widget will be tested!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    sleep_ms(3000);

    (*video)
        .setFrameBuffer(&fbMenu)
        .display();


    char menuString[] = "NEW_FILE;New File|OPEN_FILE;Open File...|SAVE;Save file|SAVE_AS;Save as|SEPARATOR;Separator|INFO;Information|RESTART;Restart|ABOUT;About|EXIT;exit|ITEM1;item1|ITEM2;item2";

    (*menu)
        .reset()
        .setTitle({"Main menu"})
        .parseMenuString(menuString)
        .setCallback(&menucb)
        .render()
        .run(video, keyboard);

    sleep_ms(2000);

    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"MENU teste finished!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    sleep_ms(5000);

    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"Msgbox widget will be tested!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    sleep_ms(3000);

   (*video)
        .setFrameBuffer(&fbMsgbox)
        .display();

   (*msgbox)
        .reset()
        .setTitle({"Greetings"})
        .setMessage({"What do you think?"})
        .setButtonType(MsgBoxEngine::YESNOCANCEL_BUTTON)
        .setIconType(MsgBoxEngine::QUESTION_ICON)
        .setCallback(&msgcb)
        .render()
        .run(video, keyboard);

    uart_puts(rpi2040uart.getUart(), "saiu");
    uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());

    sleep_ms(3000);

    (*msgbox)
        .reset()
        .setTitle({"Greetings"})
        .setMessage({"Welcome to system"})
        .setButtonType(MsgBoxEngine::OK_BUTTON)
        .setIconType(MsgBoxEngine::NO_ICON)
        .setCallback(&msgcb)
        .render()
        .run(video, keyboard);

    uart_puts(rpi2040uart.getUart(), "2");

    sleep_ms(3000);

    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"Menu widget will be tested again!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    sleep_ms(3000);

    (*video)
        .setFrameBuffer(&fbMenu)
        .display();

    (*menu)
        .reset()
        .setTitle({"Main menu 2"})
        .parseMenuString(menuString)
        .setCallback(&menucb)
        .render()
        .run(video, keyboard);

    sleep_ms(3000);


    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"Inputbox widget will be tested!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    sleep_ms(3000);

    (*video)
        .setFrameBuffer(&fbInputbox);

    (*inputbox)
        .reset()
        .setTitle({"Numero:"})
        .setMessage({"Informe um numero:"})
        .setCallback(&inputboxcb)
        .render()
        .run(video, keyboard);

    sleep_ms(3000);


    (*video)
        .setFrameBuffer(&fbTextView);


    char aboutString[255];
    sprintf(aboutString, "Hi,\n\nThis a text view\nsample with a tinny\nscreen.\n\nCreated by:\nCleverson S A\n\nMemory available:\n%d bytes\n\nPress ENTER to\nexit!", (unsigned long)AppGlobals::getFreeHeap());

    (*textView)
        .reset()
        .setTitle({"About"})
        .parseViewString(aboutString)
        .render()
        .run(video, keyboard);

    sleep_ms(3000);

    (*splashbox)
        .setTitle({"Widget testing"})
        .setMessage({"Tests finished!"})
        .render();

    (*video)
        .setFrameBuffer(&fbSplashBox)
        .display();

    cout << "Inicializado" << endl;



}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}


bool onKeyPress(const int keyCode, const char rawKeyChar)
{
   switch(keyCode){
   case KeyboardEngine::KEY_UP:
        uart_puts(rpi2040uart.getUart(), "PARA CIMA!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_DOWN:
        uart_puts(rpi2040uart.getUart(), "PARA BAIXO!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_LEFT:
        uart_puts(rpi2040uart.getUart(), "PARA DIREITA!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_RIGHT:
        uart_puts(rpi2040uart.getUart(), "PARA ESQUERDA!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_ESCAPE:
        uart_puts(rpi2040uart.getUart(), VT100Utils::gotoXY(1,1));
        uart_puts(rpi2040uart.getUart(), VT100Utils::clearScreen());
        break;
   case KeyboardEngine::KEY_F1:
        uart_puts(rpi2040uart.getUart(), "F1!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F2:
        uart_puts(rpi2040uart.getUart(), "F2!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F3:
        uart_puts(rpi2040uart.getUart(), "F3!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F4:
        uart_puts(rpi2040uart.getUart(), "F4!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F5:
        uart_puts(rpi2040uart.getUart(), "F5!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F6:
        uart_puts(rpi2040uart.getUart(), "F6!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F7:
        uart_puts(rpi2040uart.getUart(), "F7!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F8:
        uart_puts(rpi2040uart.getUart(), "F8!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F9:
        uart_puts(rpi2040uart.getUart(), "F9!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F10:
        uart_puts(rpi2040uart.getUart(), "F10!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F11:
        uart_puts(rpi2040uart.getUart(), "F11!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_F12:
        uart_puts(rpi2040uart.getUart(), "F12!");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_ENTER:
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_HOME:
       uart_puts(rpi2040uart.getUart(), "home");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_PGDOWN:
       uart_puts(rpi2040uart.getUart(), "pgdown");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_PGUP:
       uart_puts(rpi2040uart.getUart(), "pgup");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_END:
       uart_puts(rpi2040uart.getUart(), "end");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_INS:
       uart_puts(rpi2040uart.getUart(), "insert");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_DEL:
       uart_puts(rpi2040uart.getUart(), "delete");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_BACKSPACE:
        uart_puts(rpi2040uart.getUart(), "backspace");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    case KeyboardEngine::KEY_TAB:
        uart_puts(rpi2040uart.getUart(), "tab");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
   case KeyboardEngine::KEY_ANY:
       uart_putc(rpi2040uart.getUart(), rawKeyChar);
        break;
   default:
        uart_puts(rpi2040uart.getUart(), "unknown char");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        return true;
   }

    return false;
}


void onMsgBoxReturn(const int btnSelected)
{
    switch(btnSelected)
    {
    case MsgBoxEngine::BTN_YES:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O SIM");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    case MsgBoxEngine::BTN_NO:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O NAO");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    case MsgBoxEngine::BTN_CANCEL:
        uart_puts(rpi2040uart.getUart(), "VOCE ESCOLHEU O CANCELAR");
        uart_puts(rpi2040uart.getUart(), VT100Utils::lineBreak());
        break;
    default:
        break;
    }

}
