
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

int main()
{

    int pausa = 0;
    FrameBuffer fb(4,20);


    rpi2040uart.setup();
    Rpi2040UartKeyboard rpiUartKb = Rpi2040UartKeyboard::getInstance();
    KeyboardEngine *keyboard = &rpiUartKb;

    Rpi2040UartVideo rpi2040UartVideo;
    rpi2040uart.setup();
    VideoEngine *video = &rpi2040UartVideo;

    Document doc;

    (*video)
        .setFrameBuffer(&fb);

    TextEngine textEngine(&doc, video);
    textEngine.render();

    (*video).display();
    textEngine.run(video, keyboard);




    /*Document doc;

    doc.type("123");
    doc.addNewLine();
    doc.type("456");
    doc.addNewLine();
    doc.type("789");

    ConsoleVideo consoleVideo;
    VideoEngine *video = &consoleVideo;
    (*video)
        .setFrameBuffer(&fb);

    TextEngine textEngine(&doc, video);
    textEngine.render();
    (*video).display();

    doc.addNewLine();
    doc.type("012");
    doc.cursorMoveLeft();
    doc.cursorMoveLeft();
    doc.cursorMoveLeft();
    doc.cursorMoveLeft();
    doc.triggerBackspace();
    doc.triggerBackspace();
    doc.triggerBackspace();
    doc.triggerBackspace();
    doc.cursorMoveUp();
    doc.triggerBackspace();
    doc.triggerBackspace();
    doc.triggerBackspace();
    doc.triggerBackspace();
    doc.cursorMoveDown();
    doc.cursorMoveStartOfLine();
    doc.triggerBackspace();

    textEngine.render();
    (*video)
        .display();
    //textEngine.run(video, keyboard);

*/

    cout << "Inicializado" << endl;



}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}

