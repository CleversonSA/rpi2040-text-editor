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
#ifndef DOCUMENTENGINE
#define DOCUMENTENGINE

#include "../csa_object.hpp"
#include "../document/doc_character.hpp"
#include "../document/document.hpp"
#include "../document/doc_character.hpp"
#include "widget_engine.hpp"

/*
  The abstract document engine processing
*/
class DocumentEngine : public WidgetEngine
{
    public:
        DocumentEngine(Document *);
        ~DocumentEngine();

        void setDocument(Document *);
        Document * getDocument() const;

        void render();

        virtual bool isCursorAtEndOfViewLine() const = 0;
        virtual bool isCursorAtBottomOfView() const = 0;

        virtual void renderClearView() = 0;
        virtual void renderClearLine() = 0;
        virtual void renderLineBreak() = 0;
        virtual void renderCarriageReturn() = 0;
        virtual void renderCursor() = 0;
        virtual void renderTabulation() = 0;
        virtual void renderLineOverflowIndicator() = 0;
        virtual void renderLineWithOverflowIndicator() = 0;
        virtual void renderEmptyLineIndicator() = 0;
        virtual void renderLineWithContentIndicator() = 0;
        virtual void renderEOF() = 0;
        virtual void renderCharacter(DocCharacter *) = 0;
        virtual void renderColRow(int, int, int) = 0;


    private:
        Document * _document;
};

#endif // DOCCHARACTER


