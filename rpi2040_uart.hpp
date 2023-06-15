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
#ifndef RPI2040UART
#define RPI2040UART

//********************** RASPBERRY PI PICO 2040 ****************************
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"

#include "app_globals.hpp"
#include "csa_object.hpp"

/*
    RPI2040 UART Specific Helper - For TX/RX
*/
class Rpi2040Uart: public CSAObject
{
    public:

        ~Rpi2040Uart();

        static Rpi2040Uart & getInstance();

        bool isUartInitialized() const;
        void setUartInitialized(bool);

        void setup();
        void destroy();
        void defineRXIRQ(irq_handler_t);
        void disableRXIRQ();

        uart_inst_t * getUart();

        void uart_printf(char *);

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();


    private:
        Rpi2040Uart();

        static bool _uartInitialized;

        static Rpi2040Uart* _me;
};

#endif // DOCUMENT





