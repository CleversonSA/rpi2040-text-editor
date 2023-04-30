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
    if ((*getFrameBuffer()).getRow() >= (*getFrameBuffer()).getMaxRows() - 1)
    {
        return true;
    }
    return false;
}

bool TextEngine::isCursorAtEndOfViewLine() const
{
    if ((*getFrameBuffer()).getCol() >= (*getFrameBuffer()).getMaxCols() - 2)
    {
        return true;
    }
    return false;
}

void TextEngine::renderClearView()
{
    (*getFrameBuffer())
        .clearScreen()
        .cursorMoveBegin();

}

void TextEngine::renderClearLine()
{
    (*getFrameBuffer()).clearLine();
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
    if ((*getFrameBuffer()).getRow() == ((*getFrameBuffer()).getMaxRows() - 1))
    {
        (*getFrameBuffer())
            .clearScreen()
            .cursorMoveBegin()
            .cursorMoveRight();
    } else {
        (*getFrameBuffer())
            .cursorMoveDown()
            .clearLine()
            .cursorMoveStartOfLine()
            .cursorMoveRight();
    }
}

void TextEngine::renderCarriageReturn()
{
   (*getFrameBuffer())
        .cursorMoveStartOfLine()
        .cursorMoveRight();
}

void TextEngine::renderCursor()
{
    (*getFrameBuffer())
        .write('_');
}

void TextEngine::renderTabulation()
{
    (*getFrameBuffer())
        .write(' ');
}

void TextEngine::renderLineOverflowIndicator()
{
    (*getFrameBuffer())
        .gotoXY((*getFrameBuffer()).getRow(), (*getFrameBuffer()).getMaxCols() - 1)
        .fixedWrite('>');
}

void TextEngine::renderLineWithOverflowIndicator()
{
    (*getFrameBuffer())
        .gotoXY((*getFrameBuffer()).getRow(), 0)
        .fixedWrite('+');
}

void TextEngine::renderEmptyLineIndicator()
{
    (*getFrameBuffer())
        .gotoXY((*getFrameBuffer()).getRow(), 0)
        .fixedWrite('~');
}

void TextEngine::renderLineWithContentIndicator()
{
    (*getFrameBuffer())
        .gotoXY((*getFrameBuffer()).getRow(), 0)
        .fixedWrite('.');
}

void TextEngine::renderEOF()
{

}

void TextEngine::renderCharacter(DocCharacter *dc)
{
    if ((*dc).getChar() == '\0')
    {
        (*getFrameBuffer())
            .write(' ');
    } else {
        (*getFrameBuffer())
            .write((*dc).getChar());
    }
    cout << "[" << (*getFrameBuffer()).getRow() << "," << (*getFrameBuffer()).getCol() << "]" << endl;
}

void TextEngine::renderColRow()
{
    char number_array[5 + sizeof(char)];

    (*getFrameBuffer())
      .gotoXY((*getFrameBuffer()).getMaxRows() - 1, (*getFrameBuffer()).getMaxCols()-10);

    sprintf(number_array, "%d", ((*getDocument()).getDocRow()+1)+1000);

    (*getFrameBuffer())
        .write('[')
        .write(number_array[1])
        .write(number_array[2])
        .write(number_array[3]);

    sprintf(number_array, "%d", ((*getDocument()).getDocCol()+1)+1000);

    (*getFrameBuffer())
        .write(',')
        .write(number_array[1])
        .write(number_array[2])
        .write(number_array[3])
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



