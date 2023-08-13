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
#ifndef DISKENGINE_DISKENGINE_H
#define DISKENGINE_DISKENGINE_H

#include "../csa_object.hpp"

/*
  Abstract class for storage and manipulate simple files using LittleFS
*/
class DiskEngine: public CSAObject
{
public:

    static const int FILE_OPEN_CREATE = 0x01;
    static const int FILE_OPEN_READONLY = 0x02;
    static const int FILE_OPEN_READWRITE = 0x04;

    DiskEngine();
    ~DiskEngine();


    virtual char * dir(const char *) = 0;
    virtual int mkdir(const char *, const char *) = 0;
    virtual int del(const char *, const char *) = 0;
    virtual int ren(const char *, const char *, const char *) = 0;
    virtual int move(const char *, const char *, const char *) = 0;
    virtual int copy(const char *, const char *, const char *, const char *) = 0;
    virtual int touch(const char *, const char *) = 0;
    virtual void type(const char *, const char *) = 0;
    virtual int openFile(const char *, const char *, int) = 0;
    virtual void closeFile() = 0;
    virtual void write(const char) = 0;
    virtual void writeLn(const char *) = 0;
    virtual char read() = 0;
    virtual int rewind() = 0;
    virtual int getOpenedFileSize() = 0;

    virtual void indicateIOBeginStatus();
    virtual void indicateIOEndStatus();
    virtual void indicateIOErrorStatus(int);

    static DiskEngine & getInstance();
    static void setInstance(DiskEngine *);

    virtual void setup() = 0;
    virtual void destroy() = 0;
    virtual bool test() = 0;

    virtual void toString();
    virtual int getMemSize();

private:

    static DiskEngine * _diskEngineInstance;

};

#endif // DOCCHARACTER

