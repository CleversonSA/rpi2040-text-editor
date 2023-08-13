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
#include <stdio.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;


#include "pico/stdlib.h"
#include "hardware/flash.h"

#include <string.h>
#include "my_debug.h"
#include "hw_config.h"
#include "ff.h" /* Obtains integer types */
#include "diskio.h" /* Declarations of disk functions */
#include "sd_card.h"

#include "rpi2040_sdcard_disk_engine.hpp"
#include "../app_globals.hpp"


// Hardware Configuration of SPI "objects"
// Note: multiple SD cards can be driven by one SPI if they use different slave
// selects.
static spi_t spis[] = {  // One for each SPI.
        {
                .hw_inst = spi1,  // SPI component
                .miso_gpio = AppGlobals::RPI2040_SDCARD_DISK_MISO_PIN,  // GPIO number (not Pico pin number)
                .mosi_gpio = AppGlobals::RPI2040_SDCARD_DISK_MOSI_PIN,
                .sck_gpio = AppGlobals::RPI2040_SDCARD_DISK_SCK_PIN,

                // .baud_rate = 1000 * 1000
                .baud_rate = 1000000
                // .baud_rate = 25 * 1000 * 1000 // Actual frequency: 20833333.
        }};

// Hardware Configuration of the SD Card "objects"
static sd_card_t sd_cards[] = {  // One for each SD card
        {
                .pcName = "0:",   // Name used to mount device
                .spi = &spis[0],  // Pointer to the SPI driving this card
                .ss_gpio = AppGlobals::RPI2040_SDCARD_DISK_CS_PIN,    // The SPI slave select GPIO for this SD card
                .use_card_detect = true,
                .card_detect_gpio = AppGlobals::RPI2040_SDCARD_DISK_CD_PIN,  // Card detect
                .card_detected_true = 1  // What the GPIO read returns when a card is
                // present.
        }};

/* ********************************************************************** */

size_t sd_get_num() { return count_of(sd_cards); }
sd_card_t *sd_get_by_num(size_t num) {
    if (num <= sd_get_num()) {
        return &sd_cards[num];
    } else {
        return NULL;
    }
}
size_t spi_get_num() { return count_of(spis); }
spi_t *spi_get_by_num(size_t num) {
    if (num <= spi_get_num()) {
        return &spis[num];
    } else {
        return NULL;
    }
}



/* ********************************************************************** */
//  CLASS IMPLEMENTATION
/* ********************************************************************** */


FATFS *  Rpi2040SDCardDiskEngine::getFATFSPtr()
{
    return _fatFsPtr;
}


void Rpi2040SDCardDiskEngine::setFATFSPtr(FATFS * fatFSPtr)
{
    _fatFsPtr = fatFSPtr;
}


FIL * Rpi2040SDCardDiskEngine::getFILPtr()
{
    return _filPtr;
}


void Rpi2040SDCardDiskEngine::setFILPtr(FIL * filPtr)
{
    _filPtr = filPtr;
}


void Rpi2040SDCardDiskEngine::indicateIOBeginStatus()
{
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 1);
    sleep_ms(50);
}

void Rpi2040SDCardDiskEngine::indicateIOEndStatus()
{
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 0);
    sleep_ms(100);
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 1);
    sleep_ms(100);
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 0);
    sleep_ms(100);
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 1);
    sleep_ms(100);
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 0);
    sleep_ms(100);
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 1);
    sleep_ms(100);
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 0);
    sleep_ms(100);
}

bool Rpi2040SDCardDiskEngine::test()
{
    if (sd_cards[0].sd_test_com(&sd_cards[0]) == false) {
        cout << "No SD CARD detected" << endl;
        return false;
    }

    return true;
}

void Rpi2040SDCardDiskEngine::setup()
{
    DiskEngine::setInstance(this);

    indicateIOBeginStatus();

    // Initialize SD card
    if (!sd_init_driver()) {
        indicateIOErrorStatus(ERR_INIT_SDCARD);
        indicateIOEndStatus();
        return;
    }

    cout << "[RPI2040SDCardDiskEngine] SD Card initialized" << endl;

    // Mount drive
    setFATFSPtr(new FATFS);

    FRESULT fr = f_mount(getFATFSPtr(), "0:", 1);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine]ERROR: Could not mount filesystem - " << fr << endl;
        indicateIOErrorStatus(ERR_MOUNT_SDCARD);
        indicateIOEndStatus();
        return;
    }

    cout << "[RPI2040SDCardDiskEngine] SD Card system mounted" << endl;

    indicateIOEndStatus();

}




void Rpi2040SDCardDiskEngine::destroy() {
    indicateIOBeginStatus();

    // Unmount drive
    f_unmount("0:");

    indicateIOEndStatus();
}

int Rpi2040SDCardDiskEngine::rewind()
{
    FRESULT fr = f_lseek (getFILPtr(), 0);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when rewinding file" << endl;
        indicateIOErrorStatus(fr);
        return fr * -1;
    }

    return 0;
}

int Rpi2040SDCardDiskEngine::getOpenedFileSize() {
    indicateIOBeginStatus();
    int size = 0;

    indicateIOBeginStatus();
    rewind();
    while (read() !='\0') {
        size++;
    }
    rewind();
    cout << "**** O ARQUIVO TEM " << size << " byte(s) ****"<< endl;
    indicateIOEndStatus();
    return size;
}

char Rpi2040SDCardDiskEngine::read()
{
    char c = '\0';

    UINT br;
    FRESULT fr = f_read(getFILPtr(), &c, sizeof c, &br);
    if (FR_OK != fr) {
        cout << "** NAO LIDO *** " << endl;
        return '\0';
    }
    cout << "Lido: " << c << endl;
    return c;
}

void Rpi2040SDCardDiskEngine::writeLn(const char * lineStr) {
    int len = strlen(lineStr);

    for (int i = 0; i<len; i++) {
        write(lineStr[i]);
    }
}

void Rpi2040SDCardDiskEngine::write(const char c)
{
    int ret = f_putc(c, getFILPtr());
    cout << "Writing byte return = " << ret << endl;
    if (ret < 0) {
        indicateIOErrorStatus(ret);
        cout << "[RPI2040SDCardDiskEngine] ERROR: Could not write to file - " << ret << endl;
    }
}


void Rpi2040SDCardDiskEngine::closeFile()
{
    indicateIOBeginStatus();
    if(getFILPtr() == 0) {
        indicateIOEndStatus();
        return;
    }

    FRESULT fr = f_close(getFILPtr());
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when closing file" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        setFILPtr(0);
        return;
    }

    cout << "*** FILE CLOSED *** " << endl;

   indicateIOEndStatus();
}


int Rpi2040SDCardDiskEngine::openFile(const char *path, const char *fileName, int flags)
{
    int err = 0;
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    strcat(fullPathSource,path);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileName);


    indicateIOBeginStatus();

    setFILPtr(new FIL);
    BYTE mode = 0;

    if (flags & (DiskEngine::FILE_OPEN_CREATE | DiskEngine::FILE_OPEN_READWRITE)) {
        mode = FA_READ | FA_WRITE | FA_CREATE_ALWAYS ;
        cout << "Modo A Ativado" << endl;
    } else {
        cout << "Modo B Ativado" << endl;
        switch(flags) {
            case DiskEngine::FILE_OPEN_READONLY:
                mode = FA_READ;
                break;
            case DiskEngine::FILE_OPEN_READWRITE:
                mode = FA_READ | FA_WRITE;
                break;
            default:
                mode =  FA_READ | FA_WRITE | FA_CREATE_ALWAYS ;
                break;
        }
    }



    FRESULT fr = f_open(getFILPtr(),fullPathSource, mode);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when openning file" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        if (getFILPtr() != 0) {
            delete getFILPtr();
        }

        setFILPtr(0);
        return fr * -1;
    }

    indicateIOEndStatus();
    return 0;
}


void Rpi2040SDCardDiskEngine::type(const char *path, const char *fileName)
{
    int err = 0;
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    strcat(fullPathSource,path);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileName);


    indicateIOBeginStatus();

    // TODO
    cout << "[RPI2040SDCardDiskEngine] Type command not implemented!" << endl;

    indicateIOEndStatus();

}

int Rpi2040SDCardDiskEngine::mkdir(const char *path, const char *directoryName)
{
    char fullPath[255];
    fullPath[0] = '\0';

    strcat(fullPath,path);
    strcat(fullPath,"/");
    strcat(fullPath,directoryName);


    indicateIOBeginStatus();

    FRESULT fr = f_mkdir(fullPath);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when creating directory " << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        return fr * -1;
    }

    indicateIOEndStatus();

    return 0;
}


int Rpi2040SDCardDiskEngine::ren(const char *path, const char *fileNameSource, const char *fileNameDest)
{
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    strcat(fullPathSource,path);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileNameSource);

    strcat(fullPathDest,path);
    strcat(fullPathDest,"/");
    strcat(fullPathDest,fileNameSource);

    indicateIOBeginStatus();

    FRESULT fr = f_rename(fullPathSource, fullPathDest);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when renaming file" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        return fr * -1;
    }

    indicateIOEndStatus();


    return 0;
}


int Rpi2040SDCardDiskEngine::move(const char *pathSource, const char *fileNameSource, const char *pathDest)
{
    indicateIOBeginStatus();

    int err = copy(pathSource,fileNameSource,pathDest,fileNameSource);
    if (err < 0) {

        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        return err;
    }

    return del(pathSource,fileNameSource);
}

int Rpi2040SDCardDiskEngine::copy(const char *pathSource, const char *fileNameSource, const char *pathDest, const char *fileNameDest)
{
    int err = 0;
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    indicateIOBeginStatus();

    strcat(fullPathSource,pathSource);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileNameSource);

    strcat(fullPathDest,pathDest);
    strcat(fullPathDest,"/");
    strcat(fullPathDest,fileNameDest);


    FIL fSource;
    FIL fDest;

    FRESULT fr = f_open(&fSource,fullPathSource, FA_READ);
    if (fr != FR_OK) {
        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        return fr * -1;
    }

    fr = f_open(&fSource,fullPathDest, FA_WRITE | FA_CREATE_ALWAYS );
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when copying file on source" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        f_close(&fSource);
        return fr * -1;
    }

    char aByte = '\0';
    while(f_gets(&aByte,1, &fSource)) {
        f_putc(aByte, &fDest);
    }

    f_close(&fDest);
    f_close(&fSource);

    indicateIOEndStatus();
    return 0;
}

int Rpi2040SDCardDiskEngine::touch(const char *path, const char *fileName)
{
    int err = 0;
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    indicateIOBeginStatus();
    strcat(fullPathSource,path);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileName);


    FIL fSource;

    FRESULT fr = f_open(&fSource,fullPathSource, FA_WRITE | FA_CREATE_ALWAYS);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when touching file" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        return fr  * -1;
    }
    char aByte = '\0';
    f_putc(aByte, &fSource);

    f_close(&fSource);

    indicateIOEndStatus();
    return 0;
}

int Rpi2040SDCardDiskEngine::del(const char * path, const char * fileNameOrDir)
{
    char fullPath[255];
    fullPath[0] = '\0';

    strcat(fullPath,path);
    strcat(fullPath,"/");
    strcat(fullPath,fileNameOrDir);

    indicateIOBeginStatus();

    FRESULT fr = f_unlink(fullPath);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when deleting file" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        return fr * -1;
    }

    indicateIOEndStatus();

    return 0;
}

char * Rpi2040SDCardDiskEngine::dir(const char *path)
{
    char * fileLstStr = new char[1024];
    char fileNameStr[255];
    static const char *prefixes[] = {"", "K", "M", "G"};
    int idPrefix = 0;
    uint16_t size = 0;

    indicateIOBeginStatus();

    fileLstStr[0] = '\0';
    fileNameStr[0]= '\0';

    DIR dir;
    FILINFO fInfo;

    FRESULT fr = f_opendir (&dir, path);
    if (fr != FR_OK) {
        cout << "[RPI2040SDCardDiskEngine] Error when opening dir" << endl;

        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        return fileLstStr;
    }


    fr = f_findfirst (&dir, &fInfo, path, "*.*");	/* Find first file */
    if (fr != FR_OK) {

        cout << "[RPI2040SDCardDiskEngine] Error when find first file of dir" << endl;
        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        f_closedir(&dir);
        return fileLstStr;
    }

    fr = f_readdir (&dir, &fInfo);
    if (fr != FR_OK) {

        cout << "[RPI2040SDCardDiskEngine] Error when reading dir content" << endl;
        indicateIOErrorStatus(fr);
        indicateIOEndStatus();
        f_closedir(&dir);
        return fileLstStr;
    }

    if(fInfo.fattrib == AM_DIR) {
        sprintf(fileNameStr, "DIR;%s <DIR>|", fInfo.fname);
    } else {
        if (strcmp(fInfo.fname,"") != 0)
        {
            idPrefix = 0;
            size = fInfo.fsize;
            if (fInfo.fsize > (1024 * 1024 * 1024)) {
                idPrefix = 3;
                size =  fInfo.fsize / (1024 * 1024 * 1024);
            } else if (fInfo.fsize > (1024 * 1024)) {
                idPrefix = 2;
                size =  fInfo.fsize / (1024 * 1024);
            } else if (fInfo.fsize > (1024)) {
                idPrefix = 1;
                size =  fInfo.fsize / (1024);
            }
            sprintf(fileNameStr, "%s;%-13.13s%*u%sB|", fInfo.fname, fInfo.fname,  4-(idPrefix != 0), size, prefixes[idPrefix]);


        }
    }
    strcat(fileLstStr,  fileNameStr);


    while (f_findnext (&dir, &fInfo) == FR_OK) {

        if (strcmp(fInfo.fname,"") == 0)
        {
            break;
        }

        if(fInfo.fattrib == AM_DIR) {
            sprintf(fileNameStr, "DIR;%s <DIR>|", fInfo.fname);
        } else {
            idPrefix = 0;
            size = fInfo.fsize;
            if (fInfo.fsize > (1024 * 1024 * 1024)) {
                idPrefix = 3;
                size =  fInfo.fsize / (1024 * 1024 * 1024);
            } else if (fInfo.fsize > (1024 * 1024)) {
                idPrefix = 2;
                size =  fInfo.fsize / (1024 * 1024);
            } else if (fInfo.fsize > (1024)) {
                idPrefix = 1;
                size =  fInfo.fsize / (1024);
            }
            sprintf(fileNameStr, "%s;%-13.13s%*u%sB|", fInfo.fname, fInfo.fname,  4-(idPrefix != 0), size, prefixes[idPrefix]);
        }
        strcat(fileLstStr,  fileNameStr);

        cout << fileLstStr << endl;

    }

    f_closedir (&dir);


    indicateIOEndStatus();
    return fileLstStr;
}

void Rpi2040SDCardDiskEngine::toString()
{
    cout << "[Rpi2040SDCardDiskEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Rpi2040SDCardDiskEngine::getMemSize()
{
    return sizeof((*this));
}

Rpi2040SDCardDiskEngine::~Rpi2040SDCardDiskEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040SDCardDiskEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040SDCardDiskEngine::Rpi2040SDCardDiskEngine():
        DiskEngine(),
        _fatFsPtr(0),
        _filPtr(0)
{
    gpio_init(AppGlobals::RPI2040_DISK_IO_LED_PIN);
    gpio_set_dir(AppGlobals::RPI2040_DISK_IO_LED_PIN, GPIO_OUT);
}
