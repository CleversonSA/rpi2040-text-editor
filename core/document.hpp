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

#include "../csa_object.hpp"
#include "doc_row.hpp"

class Document: public CSAObject
{
    public:
        Document();
        ~Document();

        void setDocFileName(const char *);
        void setStartRowPtr(DocRow *);
        void setCurrentRowPtr(DocRow *);
        void setEnabledLineWarp(bool);
        void setDocumentChanged(bool);
        char * getDocFileName() const;
        int getDocRow() const;
        int getDocCol() const;
        int getDocRowEOF() const;
        DocRow * getStartRowPtr() const;
        DocRow * getCurrentRowPtr() const;
        bool isEnabledLineWarp() const;
        bool hasDocumentChanged() const;

        DocRow * rowAt(int);
        Document & addNewLine();
        Document & addNewLine(int pos);
        Document & triggerBackspace();
        Document & cursorMoveUp();
        Document & cursorMoveDown();
        Document & cursorMoveLeft();
        Document & cursorMoveRight();
        Document & cursorMoveEndLine();
        Document & cursorMoveStartOfLine();
        Document & cursorMoveBegin();
        Document & type(const char[]);
        Document & type(const char);
        Document & joinNextLine();

        void destroy();

        virtual void toString();
        virtual int getMemSize();

    private:

        DocRow * _startRowPtr;
        DocRow * _currentRowPtr;
        char * _docFileName;
        bool _enableLineWarp;
        bool _documentChanged = false;

        DocRow * rowAt(DocRow *, int);
};

#endif // DOCUMENT
