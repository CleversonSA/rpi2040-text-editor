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

#include <cstdio>
using std::sprintf;

#include "document_engine.hpp"
#include "app_globals.hpp"
#include "doc_row.hpp"
#include "doc_character.hpp"

void DocumentEngine::render()
{
    bool hasLineContent = false;
    int lastDocRow = (*getDocument()).getDocRow();
    int lastDocCol = (*getDocument()).getDocCol();
    char tmp[100];

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

            sprintf(tmp, "[%d] <- [%d](%c) -> [%d]", (*cPtr).getPreviousCharPtr(),cPtr, (*cPtr).getChar(),(*cPtr).getNextCharPtr());
            cout << tmp << endl;

            /*sprintf(tmp, "(%d,%d,%d,%d)", c+1, r+1, lastDocCol, lastDocRow);
            int w = sizeof(tmp)/sizeof(tmp[0]);

            for (int z=0; z < w; z++)
            {
                if (tmp[z] == '\0')
                    break;
                DocCharacter d(tmp[z],0,0);
                renderCharacter(&d);
            }*/

            if(isCursorAtEndOfViewLine())
            {
                renderLineOverflowIndicator();
                renderLineWithOverflowIndicator();
                if ((lastDocCol < (c+1)) || (lastDocRow != (r+1)))
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

                    sprintf(tmp, "(%d)", rPtr);
                    int w = sizeof(tmp)/sizeof(tmp[0]);

                    for (int z=0; z < w; z++)
                    {
                        if (tmp[z] == '\0')
                            break;
                        DocCharacter d(tmp[z],0,0);
                        renderCharacter(&d);
                    }

                }
            }

            if (lastDocRow == (r+1) && lastDocCol == 0 && (c==0))
            {
                renderCursor();
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

            if (lastDocRow == (r+1) && (lastDocCol == c) && (lastDocCol > 0))
            {
                renderCursor();
            }

            (*getDocument()).cursorMoveRight();
        }


        if (lastDocRow == (r+1) && (lastDocCol == (*rPtr).getLength()) && (lastDocCol > 0))
        {
            renderCursor();
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
WidgetEngine(),
_document(document)
{

}


