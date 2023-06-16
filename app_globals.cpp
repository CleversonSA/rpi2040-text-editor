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
#include "app_globals.hpp"
#include <malloc.h>
#include <inttypes.h>

#include <cstring>
using std::strcpy;
using std::strlen;

AppGlobals * AppGlobals::_me = 0;
const char AppGlobals::MENU_ITEM_DELIM[] = "|";
const char AppGlobals::MENU_ITEM_DETAIL_DELIM[] = ";";

void AppGlobals::setEnableObjDelLog(const bool opt)
{
    _enableObjDelLog = opt;
}

bool AppGlobals::getEnableObjDelLog() const
{
    return _enableObjDelLog;
}

uint32_t AppGlobals::getTotalHeap(void)
{
   //extern char __StackLimit, __bss_end__;

   //return &__StackLimit  - &__bss_end__;
   return 0;
}

uint32_t AppGlobals::getFreeHeap(void)
{
   //struct mallinfo m = mallinfo();

   //return AppGlobals::getTotalHeap() - m.uordblks;

   return 0;
}

int AppGlobals::calculateSimpleChecksum(char *array, int length)
{
    //Code fom https://itecnote.com/tecnote/calculating-a-16-bit-checksum/

    volatile size_t l = (int)length; // This is the length of the data
    volatile uint16_t checksum = 0;
    volatile size_t even_length = length - length%2; // Round down to multiple of 2
    volatile int i = 0;

    for (i = 0; i < even_length; i += 2) {
        volatile uint16_t val = array[i] + 256 * array[i+1];
        checksum += val;
    }

    if (i < length) { // Last byte if it's odd length
        checksum += array[i];
    }

    return checksum;
}

AppGlobals& AppGlobals::getInstance()
{
    if (AppGlobals::_me == 0)
    {
        AppGlobals::_me = new AppGlobals();
    }
    return (*AppGlobals::_me);
}

AppGlobals::AppGlobals():
    _enableObjDelLog(false)
{

}
