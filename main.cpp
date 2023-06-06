
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
#include "video_engine.hpp"

#include "lcd4x20_msgbox.hpp"
#include "lcd4x20_inputbox.hpp"
#include "lcd4x20_splashbox.hpp"
#include "lcd4x20_menu.hpp"
#include "lcd4x20_textview.hpp"

#include "console_video.hpp"


//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#define UART_ID uart0
#define BAUD_RATE 115200

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1



int getMemSize(CSAObject *);
bool onKeyPress(int keyCode, const char rawKeyChar);

// RX interrupt handler
void on_uart_rx() {
    while (uart_is_readable(UART_ID)) {
        uint8_t ch = uart_getc(UART_ID);
        // Can we send it back?
        if (uart_is_writable(UART_ID)) {
            uart_puts(UART_ID, "\033[12;10H");
            uart_puts(UART_ID, "\033[5m");
            uart_puts(UART_ID, "Last char received: ");
            uart_putc(UART_ID, ch);
            uart_puts(UART_ID, "\033[m");
        }
    }
}


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
    /*WinsockKeyboard winsockkeyboard(9000);
    KeyboardEngine *keyboard = &winsockkeyboard;


    (*keyboard).setCallbackfn(&onKeyPress);
    (*keyboard).setup();
    cout << "Primeiro menu" << endl;
    (*keyboard).loop();
    cout << "Segundo menu" << endl;
    (*keyboard).loop();
    (*keyboard).destroy();
    */

    cout << "Inicializado" << endl;

    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Use some the various UART functions to send out data
    // In a default system, printf will also output via the default UART

    // Send out a character without any conversions
    //uart_putc_raw(UART_ID, 'A');

    // Send out a character but do CR/LF conversions
    //uart_putc(UART_ID, 'B');

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, false);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    // Send out a string, with CR/LF conversions
    uart_puts(UART_ID, "\033[H\033[J");
    uart_puts(UART_ID, "\033[10;10H");
    uart_puts(UART_ID, "\033[4m");
    uart_puts(UART_ID, "Hi, this is VT100 lol :)");
    uart_puts(UART_ID, "\033[m");
    uart_puts(UART_ID, "\033[11;10H");
    uart_puts(UART_ID, "\033[5m");
    uart_puts(UART_ID, "Now it´s blinking");


    cout << "This is a PC compatible sample" << endl;


    while (1)
        tight_loop_contents();
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}


bool onKeyPress(int keyCode, const char rawKeyChar)
{
    if (keyCode == KeyboardEngine::KEY_ESCAPE) {
        cout << "Menu acionado!" << endl;
        return true;
    }

    return false;
}
