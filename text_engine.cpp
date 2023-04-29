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
using std::sprintf;

#include "text_engine.hpp"
#include "app_globals.hpp"
#include "framebuffer.hpp"

bool TextEngine::isCursorAtBottomOfView() const
{
    cout << (*_framebuffer).getRow() << " | " << (*_framebuffer).getMaxRows() - 2 << endl;

    if ((*_framebuffer).getRow() == (*_framebuffer).getMaxRows() - 2)
    {
        cout << "Bottom view reached" << endl;
        return true;
    }
    return false;
}

bool TextEngine::isCursorAtEndOfViewLine() const
{
    if ((*_framebuffer).getCol() == (*_framebuffer).getMaxCols() - 2)
    {
        cout << "End of Line view reached" << endl;
        return true;
    }
    return false;
}

void TextEngine::renderClearView()
{
    (*_framebuffer).clearScreen();
}

void TextEngine::renderClearLine()
{
    (*_framebuffer).clearLine();
}

void TextEngine::setFrameBuffer (FrameBuffer *fb)
{
    _framebuffer = fb;
}

FrameBuffer * TextEngine::getFrameBuffer() const
{
    return _framebuffer;
}

void TextEngine::renderLineBreak()
{
    if ((*_framebuffer).getRow() == ((*_framebuffer).getMaxRows() - 1))
    {
        (*_framebuffer)
            .clearScreen()
            .cursorMoveBegin();
    } else {
        (*_framebuffer)
            .cursorMoveDown()
            .clearLine()
            .cursorMoveStartOfLine();
    }
}

void TextEngine::renderCarriageReturn()
{
   (*_framebuffer)
        .cursorMoveStartOfLine();
}

void TextEngine::renderCursor()
{
    (*_framebuffer)
        .write('_');
}

void TextEngine::renderTabulation()
{
    (*_framebuffer)
        .write(' ');
}

void TextEngine::renderLineOverflowIndicator()
{
    (*_framebuffer)
        .gotoXY((*_framebuffer).getRow(), (*_framebuffer).getMaxCols() - 1)
        .fixedWrite('>');
}

void TextEngine::renderLineWithOverflowIndicator()
{
    (*_framebuffer)
        .gotoXY((*_framebuffer).getRow(), 0)
        .fixedWrite('+');
}

void TextEngine::renderEmptyLineIndicator()
{
    (*_framebuffer)
        .gotoXY((*_framebuffer).getRow(), 0)
        .fixedWrite('~');
}

void TextEngine::renderLineWithContentIndicator()
{
    (*_framebuffer)
        .gotoXY((*_framebuffer).getRow(), 0)
        .fixedWrite('.');
}

void TextEngine::renderEOF()
{

}

void TextEngine::renderCharacter(DocCharacter *dc)
{
    if ((*dc).getChar() == '\0')
    {
        (*_framebuffer)
            .write(' ');
    } else {
        (*_framebuffer)
            .write((*dc).getChar());
    }
}

void TextEngine::renderColRow()
{
    char number_array[5 + sizeof(char)];

    (*_framebuffer)
      .gotoXY((*_framebuffer).getMaxRows() - 1, (*_framebuffer).getMaxCols()-10);

    sprintf(number_array, "%d", (*_framebuffer).getRow()+1);

    (*_framebuffer)
        .write('[')
        .write(number_array[0])
        .write(number_array[1])
        .write(number_array[2]);

    sprintf(number_array, "%d", (*_framebuffer).getCol()+1);

    (*_framebuffer)
        .write(',')
        .write(number_array[0])
        .write(number_array[1])
        .write(number_array[2])
        .write(']');
}

void TextEngine::toString()
{
    cout << "[TextEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextEngine::getMemSize()
{
    return sizeof((*this));
}

TextEngine::~TextEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextEngine::TextEngine(Document * document, FrameBuffer *framebuffer):
DocumentEngine(document),
_framebuffer(framebuffer)
{

}



