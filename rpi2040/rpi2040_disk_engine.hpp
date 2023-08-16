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
#ifndef RPI2040_DISKENGINE_H
#define RPI2040_DISKENGINE_H

#include "../csa_object.hpp"
#include "../lib/lfs_disk_engine.hpp"
#include "../lib/littlefs/lfs.h"



/*
  Storage littleFS implementation for Rpi2040 specific
*/
class Rpi2040DiskEngine: public LFSDiskEngine
{
public:

    Rpi2040DiskEngine();
    ~Rpi2040DiskEngine();

    virtual int readBlockDeviceFn(const struct lfs_config *, lfs_block_t, lfs_off_t, void *, lfs_size_t);
    virtual int programBlockDeviceFn(const struct lfs_config *, lfs_block_t, lfs_off_t, const void *, lfs_size_t);
    virtual int eraseBlockDeviceFn(const struct lfs_config *, lfs_block_t);
    virtual int syncBlockDeviceFn(const struct lfs_config *);

    virtual void indicateIOBeginStatus();
    virtual void indicateIOEndStatus();

    virtual lfs_size_t getBlockDeviceCount();

    virtual void setup();

    virtual bool test();

    virtual void toString();
    virtual int getMemSize();


private:



};

#endif // DOCCHARACTER

