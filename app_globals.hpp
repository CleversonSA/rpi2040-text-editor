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
#ifndef APPGLOBALS
#define APPGLOBALS

#include <malloc.h>
#include <inttypes.h>
#include "engine/disk_engine.h"

/*
  Global settings class
*/
class AppGlobals
{
    public:
        static const char APP_VERSION[];

        static const int MAX_MENU_ITEMS_COUNT = 100;
        static const int MAX_VIEW_TEXT_SIZE = 4096;
        static const char MENU_ITEM_DELIM[];
        static const char MENU_ITEM_DETAIL_DELIM[];

        static const int RPI2040_UART_RX_WAIT_MS = 100;
        static const int RPI2040_USB_IO_LED_PIN = 19;
        static const int RPI2040_DISK_IO_LED_PIN = 18;

        static const int FRAMEBUFFER_MAX_ROWS = 4;
        static const int FRAMEBUFFER_MAX_COLS = 20;

        static const char STORAGE_DOCUMENTS_DIR[];

        ~AppGlobals();

        static AppGlobals & getInstance();

        static uint32_t getFreeHeap();
        static uint32_t getTotalHeap();
        static int calculateSimpleChecksum(char *array, int length);
        static int calculateChecksum(char *, uint16_t, int, size_t);

        void setEnableObjDelLog(const bool);
        bool getEnableObjDelLog() const;
        void setLastOpennedDocument(const char *);
        char * getLastOpennedDocument();

        void loadConstants();
        void saveConstants();

    private:
        AppGlobals();

        static AppGlobals* _me;

        char * loadProperty(DiskEngine *, char *);

        bool _enableObjDelLog = true;
        char * _lastOpennedDocument;

};

#endif // DOCCHARACTER
