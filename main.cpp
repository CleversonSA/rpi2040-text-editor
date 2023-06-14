
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
/*#include "rpi2040_uart.hpp"
#include "rpi2040_uart_keyboard.hpp"
#include "rpi2040_uart_video.hpp"

#include "msgbox_sample_callback.hpp"
#include "menu_sample_callback.hpp"
#include "inputbox_sample_callback.hpp"
*/

//********************** RASPBERRY PI PICO TEST ****************************
/*#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "pico/time.h"

Rpi2040Uart rpi2040uart = Rpi2040Uart::getInstance();
*/

int getMemSize(CSAObject *);

int main()
{

    int pausa = 0;
    FrameBuffer fb(24,40);

    /*rpi2040uart.setup();
    Rpi2040UartKeyboard rpiUartKb = Rpi2040UartKeyboard::getInstance();
    KeyboardEngine *keyboard = &rpiUartKb;

    Rpi2040UartVideo rpi2040UartVideo;
    rpi2040uart.setup();
    VideoEngine *video = &rpi2040UartVideo;*/


    ConsoleVideo consoleVideo;
    VideoEngine *video = &consoleVideo;

    (*video)
        .setFrameBuffer(&fb);


    Document doc;
    TextEngine textEngine(&doc, video);

    doc.type('1');
    doc.type('2');
    doc.type('3');

    doc.cursorMoveLeft();
    doc.cursorMoveLeft();
    textEngine.render();
    (*video)
        .display();
    cin >> pausa;

    doc.addNewLine();
    textEngine.render();
    (*video)
        .display();

    cin >> pausa;
    doc.type('4');
    doc.type('5');
    doc.type('6');


    doc.cursorMoveLeft();
    textEngine.render();
    (*video)
        .display();
    cin >> pausa;

    doc.cursorMoveLeft();
    textEngine.render();
    (*video)
        .display();
    doc.addNewLine(doc.getDocRow());
    textEngine.render();
    (*video)
        .display();

    cin >> pausa;

    doc.cursorMoveRight();
    textEngine.render();
    (*video)
        .display();
    textEngine.render();
    (*video)
        .display();


    doc.type('7');
    doc.type('\n');
    doc.type({"Salamandra"});
    doc.cursorMoveLeft();
    doc.type({" manca"});
    textEngine.render();
    (*video)
        .display();





    //textEngine.run(video, keyboard);


    cout << "Inicializado" << endl;



}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}

