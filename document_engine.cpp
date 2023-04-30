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
    bool hasLineContent = false;
    int lastDocRow = (*getDocument()).getDocRow();
    int lastDocCol = (*getDocument()).getDocCol();

    renderClearView();
    (*_document)
        .cursorMoveBegin();


    for (int r = 0; r < (*getDocument()).getDocRowEOF(); r++)
    {
        DocRow * rPtr = (*getDocument()).getCurrentRowPtr();

        if (isCursorAtBottomOfView()
            && (lastDocRow < r)) {
            break;
        }

        if (isCursorAtBottomOfView()) {
            renderClearView();
        }

        renderEmptyLineIndicator();
        hasLineContent = false;

        for (int c = 0; c < (*rPtr).getLength(); c++ )
        {
            // FIXME Slow as f*ck, please do it with a iterator
            DocCharacter * cPtr = (*rPtr).charPtrAt(c);

            if(isCursorAtEndOfViewLine())
            {
                renderLineOverflowIndicator();
                renderLineWithOverflowIndicator();
                if ((lastDocCol < c)
                    || (lastDocRow != r))
                {
                    break;
                } else {
                    renderCarriageReturn();
                    renderClearLine();
                }
            } else {
                if (!hasLineContent)
                {
                    renderLineWithContentIndicator();
                    renderCarriageReturn();
                    hasLineContent = true;
                }
            }

            switch((*cPtr).getChar())
            {
            case '\0':
            case '\n':
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

            if (lastDocRow == r &&
                ((lastDocCol == (c+1))
                 || (lastDocCol == c)))
            {
                renderCursor();
            }

            (*getDocument()).cursorMoveRight();
        }

        (*getDocument())
            .cursorMoveDown()
            .cursorMoveStartOfLine();
        renderLineBreak();

    }

    renderEOF();
    (*getDocument()).setDocCol(lastDocCol);
    (*getDocument()).setDocRow(lastDocRow);
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


