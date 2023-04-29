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
#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <cstring>
using std::strlen;

#include "document_engine.hpp"
#include "app_globals.hpp"
#include "doc_row.hpp"
#include "doc_character.hpp"

void DocumentEngine::render()
{
    bool hasLineOverflow = false;
    bool hasRowOverflow = false;
    bool interruptRender = false;
    int lastDocRow = (*getDocument()).getDocRow();
    int lastDocCol = (*getDocument()).getDocCol();

    renderClearView();
    (*_document)
        .cursorMoveBegin();

    for (int r = 0; r < (*getDocument()).getDocRowEOF(); r++)
    {
        DocRow * rPtr = (*getDocument()).getCurrentRowPtr();
        hasLineOverflow = false;
        interruptRender = false;

        renderEmptyLineIndicator();

        for (int c = 0; c < (*rPtr).getLength(); c++ )
        {
            // FIXME Slow as f*ck, please do it with a iterator
            DocCharacter * cPtr = (*rPtr).charPtrAt(c);

            if((isCursorAtEndOfViewLine()
               && isCursorAtBottomOfView()
               && ((*getDocument()).getDocRow() < lastDocRow))
               || hasRowOverflow == true)
            {
                renderClearView();
                hasRowOverflow = true;
                cout << "Line overflow reached" << endl;
            } else if (isCursorAtEndOfViewLine()
               && isCursorAtBottomOfView()) {
                interruptRender = true;
                cout << "Interrupted render" << endl;
                break;
            }


            if(isCursorAtEndOfViewLine() || hasLineOverflow) {
                renderLineOverflowIndicator();
                renderLineWithContentIndicator();
                renderCarriageReturn();
                renderClearLine();
                hasLineOverflow = true;
            }

            switch((*cPtr).getChar())
            {
            case '\0':
            case '\n':
                renderLineBreak();
                break;
            case '\t':
                renderTabulation();
                break;
            case '\r':
                renderCarriageReturn();
                break;
            case '\b':
                break;
            default:
                renderCharacter(cPtr);
                break;
            }

            if ((*getDocument()).getDocRow() == r && (*getDocument()).getDocCol() == c)
            {
                renderCursor();
            }

            (*getDocument()).cursorMoveRight();
        }

        if (interruptRender == true)
        {
            break;
        }

        (*getDocument()).cursorMoveDown();
        (*getDocument()).getCurrentRowPtr()->toString
        ();
    }

    renderEOF();
    renderColRow();

}

 void DocumentEngine:: setDocument(Document * document)
 {
     _document = document;
 }


 Document * DocumentEngine::getDocument() const
 {
     return _document;
 }


DocumentEngine::~DocumentEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[DocumentEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

DocumentEngine::DocumentEngine(Document * document):
CSAObject(),
_document(document)
{

}


