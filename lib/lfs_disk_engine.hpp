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
#ifndef LFS_DISK_ENGINE_H
#define LFS_DISK_ENGINE_H

#include "../csa_object.hpp"
#include "littlefs/lfs.h"
#include "../engine/disk_engine.h"

/*
  Abstract class for storage and manipulate simple files using LittleFS
*/
class LFSDiskEngine: public DiskEngine
{
public:


    LFSDiskEngine();
    ~LFSDiskEngine();

    virtual int readBlockDeviceFn(const struct lfs_config *, lfs_block_t, lfs_off_t, void *, lfs_size_t) = 0;
    virtual int programBlockDeviceFn(const struct lfs_config *, lfs_block_t, lfs_off_t, const void *, lfs_size_t) = 0;
    virtual int eraseBlockDeviceFn(const struct lfs_config *, lfs_block_t) = 0;
    virtual int syncBlockDeviceFn(const struct lfs_config *) = 0;

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

    virtual lfs_size_t getBlockDeviceCount() = 0;

    lfs_size_t getBlockSizeBytes() const;
    lfs_size_t getFlashPageSize() const;
    lfs_size_t getFlashStorageBytes() const;
    struct lfs_config * getLFSConfigPtr();
    lfs_t * getLfsPtr();
    lfs_file_t * getFilePtr();

    void setBlockSizeBytes(lfs_size_t blockSizeBytes );
    void setFlashPageSize(lfs_size_t flashPageSize);
    void setFlashStorageBytes(lfs_size_t flashStorageBytes);
    void setLFSConfigPtr(struct lfs_config *);
    void setLfsPtr(lfs_t *);
    void setFilePtr(lfs_file_t *);

    virtual void indicateIOBeginStatus();
    virtual void indicateIOEndStatus();
    virtual void indicateIOErrorStatus(int);

    static LFSDiskEngine & getInstance();
    static void setInstance(LFSDiskEngine *);

    virtual void setup() = 0;
    virtual void destroy();
    virtual bool test() = 0;


private:

    static LFSDiskEngine * _lfsDiskEngineInstance;

    lfs_size_t _flashPageSize = 256;
    lfs_size_t _blockSizeBytes = 4096;
    lfs_size_t _flashStorageBytes = (1408 * 1024);

    // variables used by the filesystem
    lfs_t * _lfsPtr;
    lfs_file_t * _filePtr;

    struct lfs_config * _lfsConfigPtr;

};

#endif // DOCCHARACTER

