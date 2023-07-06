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
#ifndef DOCCHARACTER
#define DOCCHARACTER

#include "../csa_object.hpp"
/*
  The minimum part of a core, a character, that indicates the next and
  previous one
*/
class DocCharacter : public CSAObject
{
    public:
        DocCharacter(char, DocCharacter * = 0, DocCharacter * = 0);
        ~DocCharacter();
        char getChar() const;
        DocCharacter *getNextCharPtr() const;
        DocCharacter *getPreviousCharPtr() const;
        void setChar(const char);
        void setNextCharPtr(DocCharacter *);
        void setPreviousCharPtr(DocCharacter *);
        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();

    private:

        char _character = '\0';
        DocCharacter *_previousCharPtr;
        DocCharacter *_nextCharPtr;

};

#endif // DOCCHARACTER
