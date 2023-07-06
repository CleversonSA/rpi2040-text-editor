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

//********************** RASPBERRY PI PICO TEST ****************************
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

/** Default configuration of storage */
#define HW_FLASH_STORAGE_BYTES  (1408 * 1024)
#define HW_FLASH_STORAGE_BASE   (PICO_FLASH_SIZE_BYTES - HW_FLASH_STORAGE_BYTES) // 655360

#include "littlefs/lfs.h"

#include "rpi2040_disk_engine.hpp"
#include "../app_globals.hpp"


void Rpi2040DiskEngine::indicateIOBeginStatus()
{
    gpio_put(AppGlobals::RPI2040_DISK_IO_LED_PIN, 1);
    sleep_ms(50);
}

void Rpi2040DiskEngine::indicateIOEndStatus()
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

bool Rpi2040DiskEngine::test()
{
    // read current count
    uint32_t boot_count = 0;
    lfs_file_open(getLfsPtr(), getFilePtr(), "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(getLfsPtr(), getFilePtr(), &boot_count, sizeof(boot_count));

    // update boot count
    boot_count += 1;
    lfs_file_rewind(getLfsPtr(), getFilePtr());
    lfs_file_write(getLfsPtr(), getFilePtr(), &boot_count, sizeof(boot_count));
    lfs_file_close(getLfsPtr(), getFilePtr());

    sleep_ms(10000);
    cout << "boot_count:" << boot_count << endl;

    return true;
}

void Rpi2040DiskEngine::setup()
{
    DiskEngine::setInstance(this);

    (*getLFSConfigPtr()).block_count = HW_FLASH_STORAGE_BYTES / getBlockSizeBytes(); // 352
    (*getLFSConfigPtr()).cache_size = FLASH_PAGE_SIZE; // 256
    (*getLFSConfigPtr()).lookahead_size = FLASH_PAGE_SIZE;  // 256

    // mount the filesystem
    int err = lfs_mount(getLfsPtr(), getLFSConfigPtr());

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        cerr << "[RPI2040DiskEngine] Error on mount: " << err << " - Formatting... " << endl;
        lfs_format(getLfsPtr(), getLFSConfigPtr());
        lfs_mount(getLfsPtr(), getLFSConfigPtr());
    }
}

int Rpi2040DiskEngine::readBlockDeviceFn(const struct lfs_config * lfsConfig, lfs_block_t lfsBlock, lfs_off_t lfsOff, void *buffer, lfs_size_t bufferSize)
{
    uint32_t fs_start = XIP_BASE + HW_FLASH_STORAGE_BASE;
    uint32_t addr = fs_start + (lfsBlock * (*lfsConfig).block_size) + lfsOff;
    memcpy(buffer, (unsigned char *)addr, bufferSize);
    return 0;
}


int Rpi2040DiskEngine::programBlockDeviceFn(const struct lfs_config * lfsConfig, lfs_block_t lfsBlock, lfs_off_t lfsOff, const void *buffer, lfs_size_t bufferSize)
{
    uint32_t fs_start = HW_FLASH_STORAGE_BASE;
    uint32_t addr = fs_start + (lfsBlock * (*lfsConfig).block_size) + lfsOff;

    uint32_t ints = save_and_disable_interrupts();
    flash_range_program(addr, (const uint8_t *)buffer, bufferSize);
    restore_interrupts(ints);
    return 0;
}


int Rpi2040DiskEngine::eraseBlockDeviceFn(const struct lfs_config *lfsConfig, lfs_block_t lfsBlock) {

    uint32_t fs_start = HW_FLASH_STORAGE_BASE;
    uint32_t offset = fs_start + (lfsBlock * (*lfsConfig).block_size);
    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(offset, (*lfsConfig).block_size);
    restore_interrupts(ints);

    return 0;
}


int Rpi2040DiskEngine::syncBlockDeviceFn(const struct lfs_config *lfsConfig)
{
    return 0;
}


lfs_size_t Rpi2040DiskEngine::getBlockDeviceCount(){

    return HW_FLASH_STORAGE_BYTES / getBlockSizeBytes(); // 352

}

void Rpi2040DiskEngine::toString()
{
    cout << "[Rpi2040DiskEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int Rpi2040DiskEngine::getMemSize()
{
    return sizeof((*this));
}

Rpi2040DiskEngine::~Rpi2040DiskEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[Rpi2040DiskEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

Rpi2040DiskEngine::Rpi2040DiskEngine():
   DiskEngine()
{
    gpio_init(AppGlobals::RPI2040_DISK_IO_LED_PIN);
    gpio_set_dir(AppGlobals::RPI2040_DISK_IO_LED_PIN, GPIO_OUT);
}
