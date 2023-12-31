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
#include "lfs_disk_engine.hpp"
#include "../app_globals.hpp"

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;

#include <cstring>
using std::strcat;

#include <cstdio>
using std::sprintf;

LFSDiskEngine * LFSDiskEngine::_lfsDiskEngineInstance = 0;

/**
 * Due littlefs implementation, no class pointer is supported, so I had to do a trick to wrapper the pointer
 */
int readBlockDeviceWrapperFn(const struct lfs_config *c, lfs_block_t block,  lfs_off_t off, void *buffer, lfs_size_t size)
{
    return LFSDiskEngine::getInstance().readBlockDeviceFn(c,block, off, buffer, size);
}

int programBlockDeviceWrapperFn(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
    return LFSDiskEngine::getInstance().programBlockDeviceFn(c,block, off, buffer, size);
}

int eraseBlockDeviceWrapperFn(const struct lfs_config *c, lfs_block_t block) {
    return LFSDiskEngine::getInstance().eraseBlockDeviceFn(c,block);
}

int syncBlockDeviceWrapperFn(const struct lfs_config *c)
{
    return LFSDiskEngine::getInstance().syncBlockDeviceFn(c);
}

//=================== CLASS IMPLEMENTATION ==================================
int LFSDiskEngine::rewind()
{
    int err = lfs_file_rewind(getLfsPtr(), getFilePtr());
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        return err;
    }
    return 0;
}

int LFSDiskEngine::getOpenedFileSize() {
    indicateIOBeginStatus();
    int err = lfs_file_rewind(getLfsPtr(), getFilePtr());
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        return err;
    }
    cout << "rewinding.."<< endl;

    int size = (int)lfs_file_size(getLfsPtr(), getFilePtr());

    cout << "counted"<< size << endl;

    err = lfs_file_rewind(getLfsPtr(), getFilePtr());
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        return err;
    }

    cout << "rewinding"<< endl;

    indicateIOEndStatus();

    cout << "rewinding2"<< endl;
    return size;
}

char LFSDiskEngine::read()
{

    char c = '\0';

    int err = lfs_file_read(getLfsPtr(),getFilePtr(),&c,sizeof(char));
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        return '\0';
    }


    return c;
}

void LFSDiskEngine::writeLn(const char * lineStr) {
    int len = strlen(lineStr);

    for (int i = 0; i<len; i++) {
        write(lineStr[i]);
    }
}

void LFSDiskEngine::write(const char c)
{
    lfs_file_write(getLfsPtr(),getFilePtr(),&c,sizeof(char));

}


void LFSDiskEngine::closeFile()
{
    indicateIOBeginStatus();
    if(getFilePtr() == 0) {
        indicateIOEndStatus();
        return;
    }

    int err = lfs_file_close(getLfsPtr(), getFilePtr());
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        setFilePtr(0);
        return;
    }

    //delete getFilePtr();
    setFilePtr(0);
    indicateIOEndStatus();
}


int LFSDiskEngine::openFile(const char *path, const char *fileName, int flags)
{
    int err = 0;
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    strcat(fullPathSource,path);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileName);

    if(getFilePtr() != 0) {
        lfs_file_t *aux = getFilePtr();
        setFilePtr(0);
        delete aux;
    }

    cout << "Passou aqui disk" << endl;
    lfs_file *file = new lfs_file;
    setFilePtr(file);

    cout << "Passou aqui disk 2" << endl;

    indicateIOBeginStatus();
    int lfsFlags = 0;


    if (flags & (DiskEngine::FILE_OPEN_CREATE | DiskEngine::FILE_OPEN_READWRITE)) {
        lfsFlags = LFS_O_CREAT | LFS_O_RDWR;
        cout << "Modo A Ativado" << endl;
    } else {
        cout << "Modo B Ativado" << endl;
        switch(flags) {
            case DiskEngine::FILE_OPEN_READONLY:
                lfsFlags = LFS_O_RDONLY;
                break;
            case DiskEngine::FILE_OPEN_READWRITE:
                lfsFlags = LFS_O_RDWR;
                break;
            default:
                lfsFlags =LFS_O_CREAT | LFS_O_RDWR;
                break;
        }
    }

    err = lfs_file_open(getLfsPtr(), getFilePtr(),fullPathSource,lfsFlags);
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        setFilePtr(0);
        return err;
    }

    err = lfs_file_rewind(getLfsPtr(), getFilePtr());
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        setFilePtr(0);
        return err;
    }

    indicateIOEndStatus();
    return 0;
}

void LFSDiskEngine::indicateIOBeginStatus()
{
    //Nothing, may be a LED indicator status
}

void LFSDiskEngine::indicateIOEndStatus()
{
    //Nothing, may be a LED indicator status
}

void LFSDiskEngine::indicateIOErrorStatus(int err)
{
    //Nothing, may be a LED indicator status
    cerr << "IO ERROR: " << err << endl;
}

void LFSDiskEngine::type(const char *path, const char *fileName)
{
    int err = 0;
    char fullPathSource[255];
    char fullPathDest[255];
    fullPathSource[0] = '\0';
    fullPathDest[0] = '\0';

    strcat(fullPathSource,path);
    strcat(fullPathSource,"/");
    strcat(fullPathSource,fileName);

    lfs_file file;

    indicateIOBeginStatus();
    err = lfs_file_open(getLfsPtr(), &file,fullPathSource,LFS_O_RDONLY);
    if (err < 0) {
        indicateIOErrorStatus(err);
        indicateIOEndStatus();
        return;
    }
    lfs_file_rewind(getLfsPtr(), &file);

    lfs_off_t fileSize = lfs_file_size(getLfsPtr(), &file);
    lfs_file_rewind(getLfsPtr(), &file);

    lfs_off_t byteCounter = 0;
    char byteBuffer=0;

    while (byteCounter < fileSize) {
        lfs_file_read(getLfsPtr(),&file,&byteBuffer,sizeof(char));
        cout << (char)byteBuffer;

        if (byteBuffer == '\n' || byteBuffer == '\0'){
            cout << endl;
        }
        byteCounter++;
    }
    cout << endl;

    lfs_file_close(getLfsPtr(),&file);

    indicateIOEndStatus();

}

int LFSDiskEngine::mkdir(const char *path, const char *directoryName)
{
    char fullPath[255];
    fullPath[0] = '\0';

    strcat(fullPath,path);
    strcat(fullPath,"/");
    strcat(fullPath,directoryName);

    return lfs_mkdir(getLfsPtr(),fullPath);
}


int LFSDiskEngine::ren(const char *path, const char *fileNameSource, const char *fileNameDest)
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

    return lfs_rename(getLfsPtr(), fullPathSource, fullPathDest);
}


int LFSDiskEngine::move(const char *pathSource, const char *fileNameSource, const char *pathDest)
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

int LFSDiskEngine::copy(const char *pathSource, const char *fileNameSource, const char *pathDest, const char *fileNameDest)
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

    lfs_file fileDest;
    lfs_file fileSource;


    err = lfs_file_open(getLfsPtr(), &fileSource,fullPathSource,LFS_O_RDONLY);
    if (err < 0) {
        indicateIOEndStatus();
        indicateIOErrorStatus(err);
        return err;
    }
    lfs_file_rewind(getLfsPtr(), &fileSource);

    err = lfs_file_open(getLfsPtr(), &fileDest,fullPathDest,LFS_O_CREAT | LFS_O_WRONLY);
    if (err < 0) {
        lfs_file_close(getLfsPtr(),&fileSource);
        indicateIOEndStatus();
        indicateIOErrorStatus(err);
        return err;
    }

    lfs_off_t fileSize = lfs_file_size(getLfsPtr(), &fileSource);
    lfs_file_rewind(getLfsPtr(), &fileSource);
    lfs_file_rewind(getLfsPtr(), &fileDest);

    lfs_off_t byteCounter = 0;
    char byteBuffer=0;

    while (byteCounter < fileSize) {
        lfs_file_read(getLfsPtr(),&fileSource,&byteBuffer,sizeof(char));
        lfs_file_write(getLfsPtr(),&fileDest,&byteBuffer,sizeof(char));
        byteCounter++;
    }

    lfs_file_close(getLfsPtr(),&fileSource);
    lfs_file_close(getLfsPtr(),&fileDest);

    indicateIOEndStatus();
    return 0;
}

int LFSDiskEngine::touch(const char *path, const char *fileName)
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

    lfs_file fileDest;

    err = lfs_file_open(getLfsPtr(), &fileDest,fullPathDest,LFS_O_CREAT | LFS_O_WRONLY);
    if (err < 0) {
        indicateIOEndStatus();
        indicateIOErrorStatus(err);
        return err;
    }

    lfs_file_close(getLfsPtr(),&fileDest);

    indicateIOEndStatus();
    return 0;
}

int LFSDiskEngine::del(const char * path, const char * fileNameOrDir)
{
    char fullPath[255];
    fullPath[0] = '\0';

    strcat(fullPath,path);
    strcat(fullPath,"/");
    strcat(fullPath,fileNameOrDir);

    return lfs_remove(getLfsPtr(),fullPath);
}

//From: https://github.com/littlefs-project/littlefs/issues/2
char * LFSDiskEngine::dir(const char *path)
{
    lfs_dir_t dir;
    char * fileLstStr = new char[1024];
    char fileNameStr[255];
    struct lfs_info info;
    static const char *prefixes[] = {"", "K", "M", "G"};
    indicateIOBeginStatus();

    fileLstStr[0] = '\0';
    fileNameStr[0]= '\0';

    int err = lfs_dir_open(getLfsPtr(), &dir, path);
    if (err) {
        indicateIOEndStatus();
        indicateIOErrorStatus(err);
        return 0;
    }

    while (true) {
        int res = lfs_dir_read(getLfsPtr(), &dir, &info);
        if (res < 0) {
            indicateIOEndStatus();
            indicateIOErrorStatus(err);
            return 0;
        }

        if (res == 0) {
            break;
        }


        for (int i = sizeof(prefixes)/sizeof(prefixes[0])-1; i >= 0; i--) {
            if (info.size >= (1 << 110*i)-1) {

                switch (info.type) {
                    case LFS_TYPE_REG:
                        sprintf(fileNameStr, "%s;%-13.13s%*u%sB|", info.name, info.name,  4-(i != 0), info.size >> 10*i, prefixes[i]);
                        break;
                    case LFS_TYPE_DIR:
                        sprintf(fileNameStr, "DIR;%s <DIR>|", info.name);
                        break;
                    default:
                        sprintf(fileNameStr, "UNK;%s <???>|", info.name);
                        break;
                }

                break;
            }
        }

        strcat(fileLstStr,  fileNameStr);
    }

    err = lfs_dir_close(getLfsPtr(), &dir);
    if (err) {
        indicateIOEndStatus();
        indicateIOErrorStatus(err);
        return 0;
    }

    indicateIOEndStatus();
    return fileLstStr;
}

void LFSDiskEngine::setLfsPtr(lfs_t * lfsPtr)
{
    _lfsPtr = lfsPtr;
}

void LFSDiskEngine::setFilePtr(lfs_file_t * filePtr)
{
    _filePtr = filePtr;
}

lfs_t * LFSDiskEngine::getLfsPtr()
{
    return _lfsPtr;
}

lfs_file_t * LFSDiskEngine::getFilePtr(){
    return _filePtr;
}

LFSDiskEngine & LFSDiskEngine::getInstance()
{
    return (*LFSDiskEngine::_lfsDiskEngineInstance);
}

void LFSDiskEngine::setInstance(LFSDiskEngine *_lfsDiskEngineInstance)
{
    LFSDiskEngine::_lfsDiskEngineInstance = _lfsDiskEngineInstance;
}

void LFSDiskEngine::setFlashStorageBytes(lfs_size_t flashStorageBytes)
{
    _flashStorageBytes = flashStorageBytes;
}

lfs_size_t  LFSDiskEngine::getFlashStorageBytes() const
{
    return _flashStorageBytes;
}

struct lfs_config * LFSDiskEngine::getLFSConfigPtr()
{
    return _lfsConfigPtr;
}

void LFSDiskEngine::setLFSConfigPtr(struct lfs_config * lfsConfigPtr)
{
    _lfsConfigPtr;
}

lfs_size_t LFSDiskEngine::getBlockSizeBytes() const
{
    return _blockSizeBytes;
}

lfs_size_t LFSDiskEngine::getFlashPageSize() const
{
    return _flashPageSize;
}

void LFSDiskEngine::setBlockSizeBytes(lfs_size_t blockSizeBytes )
{
    _blockSizeBytes = blockSizeBytes;
}

void LFSDiskEngine::setFlashPageSize(lfs_size_t flashPageSize )
{
    _flashPageSize = flashPageSize;
}

void LFSDiskEngine::destroy()
{

    if (_lfsPtr != 0)
    {
        // release any resources we were using
        lfs_unmount(_lfsPtr);
        delete _lfsPtr;
    }

    cout << "[DiskEngine] Destroyed" << endl;
}

LFSDiskEngine::~LFSDiskEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[LFSDiskEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

LFSDiskEngine::LFSDiskEngine():
        DiskEngine(),
        _lfsConfigPtr(0),
        _lfsPtr(0),
        _filePtr(0)
{
    _lfsConfigPtr = new lfs_config;
    _lfsPtr = new lfs;
    _filePtr = new lfs_file;

    // configuration of the filesystem is provided by this struct
    (*_lfsConfigPtr) = {
            // block device operations
            .read  = &readBlockDeviceWrapperFn,
            .prog  = &programBlockDeviceWrapperFn,
            .erase = &eraseBlockDeviceWrapperFn,
            .sync  = &syncBlockDeviceWrapperFn,

            // block device configuration
            .read_size = getFlashPageSize(), // 256
            .prog_size = getFlashPageSize(), // 256

            .block_size = getBlockSizeBytes(), // 4096
            .block_count = getFlashStorageBytes() / getBlockSizeBytes(), // 352
            .block_cycles = 16, // ?

            .cache_size = getFlashPageSize(), // 256
            .lookahead_size = getFlashPageSize(),   // 256
    };

    cout << "LFS Driver started" << endl;
}
