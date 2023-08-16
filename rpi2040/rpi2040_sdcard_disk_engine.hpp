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
#ifndef RPI2040_SDCARD_DISKENGINE_H
#define RPI2040_SDCARD_DISKENGINE_H

#include "../csa_object.hpp"

#include <string.h>
#include "my_debug.h"
#include "hw_config.h"
#include "ff.h" /* Obtains integer types */
#include "diskio.h" /* Declarations of disk functions */
#include "sd_card.h"

#include "../engine/disk_engine.h"


/*
  SD Card driver using no-OS-FatFS-SD-SPI-Rpi-Pico library
*/
class Rpi2040SDCardDiskEngine: public DiskEngine
{
public:

    static const int ERR_INIT_SDCARD = -50001;
    static const int ERR_MOUNT_SDCARD = -50002;

    Rpi2040SDCardDiskEngine();
    ~Rpi2040SDCardDiskEngine();


    virtual void indicateIOBeginStatus();
    virtual void indicateIOEndStatus();

    virtual char * dir(const char *);
    virtual int mkdir(const char *, const char *);
    virtual int del(const char *, const char *);
    virtual int ren(const char *, const char *, const char *);
    virtual int move(const char *, const char *, const char *);
    virtual int copy(const char *, const char *, const char *, const char *);
    virtual int touch(const char *, const char *);
    virtual void type(const char *, const char *);
    virtual int openFile(const char *, const char *, int);
    virtual void closeFile();
    virtual void write(const char);
    virtual void writeLn(const char *);
    virtual char read();
    virtual int rewind();
    virtual int getOpenedFileSize();

    virtual void setup();

    virtual bool test();


    FATFS *  getFATFSPtr();
    void setFATFSPtr(FATFS *);
    FIL * getFILPtr();
    void setFILPtr(FIL *);

    virtual void destroy();
    virtual void toString();
    virtual int getMemSize();

private:

    FATFS * _fatFsPtr;
    FIL * _filPtr;

};

#endif // DOCCHARACTER

