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
#ifndef DOCUMENT
#define DOCUMENT

#include "csa_object.hpp"
#include "doc_row.hpp"

class Document: public CSAObject
{
    public:
        Document();
        ~Document();

        void setDocFileName(const char []);
        char * getDocFileName() const;
        void setDocRow(const int);
        int getDocRow() const;
        void setDocCol(const int);
        int getDocCol() const;
        void setDocRowEOF(const int);
        int getDocRowEOF() const;
        void setStartRowPtr(DocRow *);
        DocRow * getStartRowPtr() const;
        void setCurrentRowPtr(DocRow *);
        DocRow * getCurrentRowPtr() const;

        DocRow * rowAt(int);
        Document & addNewLine();
        Document & triggerBackspace();
        Document & cursorMoveUp();
        Document & cursorMoveDown();
        Document & cursorMoveLeft();
        Document & cursorMoveRight();
        Document & type(const char[]);

        virtual void toString();
        virtual int getMemSize();

    private:

        DocRow * _startRowPtr;
        DocRow * _currentRowPtr;
        int _docRow;
        int _docCol;
        int _docRowEOF;
        char * _docFileName;

        DocRow * rowAt(DocRow *, int);
};

#endif // DOCUMENT
