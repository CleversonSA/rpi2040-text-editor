
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

#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE


int getMemSize(CSAObject *);
bool onKeyPress(int keyCode, const char rawKeyChar);


// RX interrupt handler
void on_uart_rx() {
    char ola[32];
    ola[0] = '\0';
    uint8_t ichar = 0;
    static int linha = 1;
    static uint8_t buffer[10];
    static int contador = 0;
    static int interrupcao = 0;
    while (uart_is_readable_within_us(UART_ID, 200)) {

        ichar = uart_getc(UART_ID);

        if (ichar > 0) {
            buffer[contador] = ichar;

            contador ++;
            if (contador > 9) contador = 0;
        }
    }

    if (uart_is_writable(UART_ID) && (ichar != 0)) {
        if ((linha % 10) == 0)
        {
            uart_puts(UART_ID, VT100Utils::gotoXY(1,1));
            uart_puts(UART_ID, VT100Utils::clearScreen());
            uart_puts(UART_ID, VT100Utils::inverseAttribute());
            uart_puts(UART_ID, "Vamos descobrir as teclas pressionadas!");
            uart_puts(UART_ID, VT100Utils::disableAttributes());
            uart_puts(UART_ID, VT100Utils::gotoXY(2,1));
        }
        uart_puts(UART_ID, VT100Utils::disableAttributes());
        uart_puts(UART_ID, VT100Utils::underlineAttribute());
        uart_puts(UART_ID, "Caractere recebido: [");
        //uart_putc(UART_ID, ch);
        sprintf(ola, "] - Código: [%d]", ichar);
        uart_puts(UART_ID, ola);
        for (int i = 0; i < contador; i++)
        {
            sprintf(ola, "{%d}(%c)", buffer[i], (char)buffer[i]);
            uart_puts(UART_ID, ola);
            buffer[i]=0;
        }

        uart_puts(UART_ID, VT100Utils::lineBreak());
        //uart_putc(UART_ID, ch);
        uart_puts(UART_ID, VT100Utils::disableAttributes());
        sprintf(ola, "Interrupcoes = %d", interrupcao);
        uart_puts(UART_ID, ola);
        uart_puts(UART_ID, VT100Utils::lineBreak());

        linha ++;
        contador  = 0;
    }

    interrupcao++;
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

    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, true);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

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
    uart_puts(UART_ID, VT100Utils::gotoXY(1,1));
    uart_puts(UART_ID, VT100Utils::clearScreen());
    uart_puts(UART_ID, VT100Utils::inverseAttribute());
    uart_puts(UART_ID, "Vamos descobrir as teclas pressionadas!");
    uart_puts(UART_ID, VT100Utils::disableAttributes());
    uart_puts(UART_ID, VT100Utils::gotoXY(2,1));

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
