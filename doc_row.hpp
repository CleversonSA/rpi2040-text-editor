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
#ifndef DOCROW
#define DOCROW

#include "csa_object.hpp"
#include "doc_character.hpp"

/*
  The collection of characters by row
*/
class DocRow : public CSAObject
{
    public:
        DocRow(DocCharacter * = 0, DocRow * = 0, DocRow * = 0);
        ~DocRow();

        DocCharacter * getStartCharPtr() const;
        DocRow * getPreviousRowPtr() const;
        DocRow * getNextRowPtr() const;

        void setStartCharPtr(DocCharacter *);
        void setNextRowPtr(DocRow *);
        void setPreviousRowPtr(DocRow *);
        int getSize();


        DocCharacter * charPtrAt(int);
        DocCharacter * charPtrAtEnd();

        DocRow & deletePtrAt(int);
        DocRow & append(DocCharacter *);
        DocRow & append(const char[]);
        DocRow & append(DocCharacter *, int);
        DocRow & append(const char[], int);

        void fromCharArray(const char []);
        void readAllChars ();
        void deleteAllChars();

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();

    private:

        int getSize (const DocCharacter * startCharPtr);

        DocCharacter * charPtrAt(DocCharacter *, int);
        DocCharacter * charPtrAtEnd (DocCharacter *);
        void fromCharArray(const char [], DocRow &);
        void readAllChars (const DocCharacter * startCharPtr);
        void deleteAllChars(const DocCharacter * startCharPtr);

        DocCharacter * _startCharPtr;
        DocRow * _nextRowPtr;
        DocRow * _previousRowPtr;
};

#endif // DOCCHARACTER

