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
#include "resource_collection.hpp"
#include "engine/disk_engine.h"

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <cstring>
using std::strcpy;
using std::strlen;

AppGlobals * AppGlobals::_me = 0;

const char AppGlobals::APP_VERSION[] = "0.7.5";

const char AppGlobals::MENU_ITEM_DELIM[] = "|";
const char AppGlobals::MENU_ITEM_DETAIL_DELIM[] = ";";
const char AppGlobals::STORAGE_DOCUMENTS_DIR[] = "/My Briefcase";


void AppGlobals::saveConstants()
{
    DiskEngine *disk = ResourceCollection::getInstance().getDiskEngine();

    (*disk).del(AppGlobals::STORAGE_DOCUMENTS_DIR, "settings.properties");

    cout << AppGlobals::getInstance().getFreeHeap() << " - " << AppGlobals::getInstance().getTotalHeap() << endl;

   int err = (*disk).openFile(AppGlobals::STORAGE_DOCUMENTS_DIR, "settings.properties",DiskEngine::FILE_OPEN_CREATE | DiskEngine::FILE_OPEN_READWRITE);
   if (err < 0) {
       cerr << "Failed when saving settings.properties - " << err << endl;
       return;
   }

   char *tmp = new char[100];
   tmp[0] = '\0';

   if (_lastOpennedDocument == 0) {
       strcat(tmp, "lastOpennedFile=\n");
   } else {
       strcat(tmp, "lastOpennedFile");strcat(tmp, "=");strcat(tmp, _lastOpennedDocument);strcat(tmp, "\n");
   }

   (*disk).writeLn(tmp);
   (*disk).closeFile();

}

void AppGlobals::loadConstants()
{
    DiskEngine *disk = ResourceCollection::getInstance().getDiskEngine();

    int err = (*disk).openFile(AppGlobals::STORAGE_DOCUMENTS_DIR, "settings.properties",DiskEngine::FILE_OPEN_READONLY);
    if (err < 0) {
        cerr << "Failed when openning settings.properties - " << err << endl;
        return;
    }

    setLastOpennedDocument(loadProperty(disk, "lastOpennedFile"));

    (*disk).closeFile();
}


char * AppGlobals::loadProperty(DiskEngine *disk, char * property2Find)
{
    char *property = new char[255];
    char *value = new char[255];
    property[0] = '\0';
    value[0] = '\0';


    int fileSize = (*disk).getOpenedFileSize();
    int err = (*disk).rewind();
    if (err < 0) {
        cerr << "Failed when rewinding settings.properties - " << err << endl;
        (*disk).closeFile();
        return 0;
    }

    bool propertyFound = false;
    for (int byteCounter = 0; byteCounter < fileSize; byteCounter++)
    {
        char c = (*disk).read();
        if (c == '\n' || c == '\0')
        {
            if (propertyFound == true)
            {
                break;
            }
            property[0] = '\0';
            value[0] = '\0';
        } else {
            if (propertyFound)
                strcat(value,new char[2]{c, '\0'});
            else
                strcat(property,new char[2]{c, '\0'});

            if (!propertyFound && strcmp(property,property2Find) == 0)
            {
                value[0] = '\0';
                propertyFound = true;
                (*disk).read();
                byteCounter++;
                continue;
            }
        }
    }

    return value;
}

void AppGlobals::setLastOpennedDocument(const char * filename) {
    char * fnPtr = new char[strlen(filename)+1];
    fnPtr[0] = '\0';
    strcpy(fnPtr, filename);

    _lastOpennedDocument = fnPtr;
}

char * AppGlobals::getLastOpennedDocument()
{
    return _lastOpennedDocument;
}


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
   extern char __StackLimit, __bss_end__;

   return &__StackLimit  - &__bss_end__;
}

uint32_t AppGlobals::getFreeHeap(void)
{
   struct mallinfo m = mallinfo();

   return AppGlobals::getTotalHeap() - m.uordblks;

}

int AppGlobals::calculateChecksum(char *array, uint16_t checksum, int i, size_t even_length)
{
    if (i == even_length) {
        return checksum;
    }

    volatile uint16_t val = array[i] + 256 * array[i+1];
    checksum += val;
    i+=2;

    return calculateChecksum(array, checksum, i, even_length);
}


int AppGlobals::calculateSimpleChecksum(char *array, int length)
{
    //Code fom https://itecnote.com/tecnote/calculating-a-16-bit-checksum/

    //TODO Melhorar a performance desse calculo, nao esta bom

    volatile size_t l = (int)length; // This is the length of the data
    volatile uint16_t checksum = 0;
    volatile size_t even_length = length - length%2; // Round down to multiple of 2
    volatile int i = 0;

    /*for (i = 0; i < even_length; i += 2) {
        volatile uint16_t val = array[i] + 256 * array[i+1];
        checksum += val;
    }*/
    checksum = calculateChecksum(array, checksum, i, even_length);

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
_enableObjDelLog(false),
_lastOpennedDocument(0)
{

}
