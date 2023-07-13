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
#ifndef SAVEASMENU
#define SAVEASMENU

#include "../csa_object.hpp"
#include "../engine/keyboard_engine.hpp"
#include "../engine/video_engine.hpp"
#include "document.hpp"
#include "../engine/disk_engine.h"
#include "../engine/menu_engine.hpp"

/*
  Menu selection or dialog for SAVE text file (Save and Save AS)
*/
class SaveAsMenu : public CSAObject
{
public:

    SaveAsMenu();
    ~SaveAsMenu();

    void run(bool);
    void showInputfileName();
    void showConfirmOverwite();
    void save(char *);
    void saveSilent(char *);
    void backToDocument();

    void setFileNameToSave(char *);
    char * getFileNameToSave();

    virtual void toString(); // Yes, you know, Java feelings rs
    virtual int getMemSize();

private:

    char * _fileNameToSave;


};

#endif // DOCCHARACTER
