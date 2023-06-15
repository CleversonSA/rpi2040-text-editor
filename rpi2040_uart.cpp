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

#include <cstring>
using std::strcpy;

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <iomanip>
using std::setw;

#include "rpi2040_uart.hpp"
#include "app_globals.hpp"

Rpi2040Uart * Rpi2040Uart::_me = 0;
bool    Rpi2040Uart::_uartInitialized = false;

bool Rpi2040Uart::isUartInitialized() const
{
    return (Rpi2040Uart::_uartInitialized);
}


void Rpi2040Uart::setUartInitialized(bool uartInitialized)
{
    Rpi2040Uart::_uartInitialized = true;
}


Rpi2040Uart& Rpi2040Uart::getInstance()
{
    if (Rpi2040Uart::_me == 0)
    {
        Rpi2040Uart::_me = new Rpi2040Uart();
    }
    return (*Rpi2040Uart::_me);
}


uart_inst_t * Rpi2040Uart::getUart()
{
    return UART_ID;
}

void Rpi2040Uart::setup()
{

    if (!isUartInitialized())
    {
        gpio_pull_up(1);

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

        setUartInitialized(true);

        uart_puts(UART_ID, "Inicializado!!");

    }

}


void Rpi2040Uart::defineRXIRQ(irq_handler_t handler)
{

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, handler);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

}

void Rpi2040Uart::disableRXIRQ()
{

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    //irq_set_exclusive_handler(UART_IRQ, 0);
    irq_set_enabled(UART_IRQ, false);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, false, false);

}


void  Rpi2040Uart::destroy()
{
    uart_deinit(UART_ID);

    setUartInitialized(false);
}


void Rpi2040Uart::toString()
{
    cout << "[Rpi2040Uart] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
        << endl;
}

int Rpi2040Uart::getMemSize()
{
    return sizeof((*this));
}

Rpi2040Uart::~Rpi2040Uart()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040Uart] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040Uart::Rpi2040Uart():
CSAObject()
{

}




