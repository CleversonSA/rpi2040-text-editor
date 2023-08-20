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
using std::strcat;
using std::strcpy;

#include <cstdio>
using std::sprintf;

#include "document_engine.hpp"
#include "app_globals.hpp"
#include "doc_row.hpp"
#include "doc_character.hpp"

char * DocumentEngine::renderDocCharAsStr(DocCharacter * docCharacterPtr) {
    char *nChar = new char[2];
    nChar[0] = '\0';

    if (docCharacterPtr != 0) {

        switch((*docCharacterPtr).getChar())
        {
            case '\0':
            case '\n':
            case '\t':
            case '\r':
                strcpy(nChar, "");
                break;
            default:
                sprintf(nChar,"%c", (*docCharacterPtr).getChar());
                break;
        }
        return nChar;

    } else {

        strcpy(nChar, "");
        return nChar;

    }
}

char * DocumentEngine::renderLineToStr(DocRow * rPtr)
{
    char *strContent = new char[4096];
    strContent[0] = '\0';

    if (rPtr == 0) {
        return strContent;
    }

    int rowLength = (*rPtr).getLength();
    int moves = 0;

    DocCharacter * cPtr = (*rPtr).getStartCharPtr();
    if (cPtr == 0) {
        return strContent;
    }

    while (cPtr != 0) {

        strcat(strContent, renderDocCharAsStr(cPtr));

        if ((*cPtr).getNextCharPtr() == 0) {
            break;
        }
        moves++;
        cPtr = (*cPtr).getNextCharPtr();
    }

    for (;moves >= 0;moves --) {
        cPtr = (*cPtr).getPreviousCharPtr();
    }

    return strContent;
}


void DocumentEngine::render()
{
    bool hasLineContent = false;
    int lastDocRow = (*getDocument()).getDocRow();
    int lastDocCol = (*getDocument()).getDocCol();
    int rowEOF =  (*getDocument()).getDocRowEOF();
    int rowLength = 0;
    int bytes = 0;
    char tmp[100];

    renderClearView();
    (*_document)
        .cursorMoveBegin();


    for (int r = 0; r < rowEOF; r++)
    {
        DocRow * rPtr = (*getDocument()).getCurrentRowPtr();

        if (isCursorAtBottomOfView()
            && (lastDocRow < (r+1))) {
            break;
        }

        if (isCursorAtBottomOfView()) {
            renderClearView();
        }

        renderEmptyLineIndicator();
        hasLineContent = false;
        rowLength = (*rPtr).getLength();

        for (int c = 0; c <rowLength ; c++ )
        {
            // FIXME Slow as f*ck, please do it with a iterator
            DocCharacter * cPtr = (*rPtr).getCurrentCharPtr();

            if(isCursorAtEndOfViewLine())
            {
                renderLineOverflowIndicator();
                renderLineWithOverflowIndicator();
                if (lastDocCol < (c+1) || (lastDocRow != (r+1)))
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

            if (lastDocRow == (r+1) && lastDocCol == 1 && (c==0))
            {
                renderCursor();
            }

            if (lastDocRow == (r+1) && (lastDocCol == (c+1)) && (c > 0))
            {
                renderCursor();
            }


            (*rPtr).moveNextCharPtr();
            bytes++;
        }


        renderLineBreak();
        (*getDocument()).cursorMoveDown();


    }

    renderEOF();
    (*getDocument()).cursorMoveBegin();
    for (volatile int i=1; i<lastDocRow; i++)
    {
        (*getDocument()).cursorMoveDown();
    }

    for (volatile int i=1; i<lastDocCol; i++)
    {
        (*(*getDocument()).getCurrentRowPtr()).moveNextCharPtr();
    }
    renderColRow(lastDocRow, lastDocCol, bytes);

}

 void DocumentEngine:: setDocument(Document * document)
 {
     _document = document;
 }


 Document * DocumentEngine::getDocument()
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


