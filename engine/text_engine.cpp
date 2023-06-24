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
#include "video_engine.hpp"
#include "keyboard_engine.hpp"
#include "../keyboard/textengine_keyboard_callback.hpp"


void TextEngine::run(VideoEngine *videoEngine, KeyboardEngine *keyboardEngine)
{
    (*videoEngine).display();

    TextEngineKeyboardCallback *kcb = new TextEngineKeyboardCallback;

    (*kcb).setVideoEngine(videoEngine);
    (*kcb).setTextEngine(this);

    (*keyboardEngine).setup();
    (*keyboardEngine).setCallback(kcb);
    (*keyboardEngine).loop();

    delete kcb;
}


VideoEngine * TextEngine::getVideoEngine() const
{
    return _videoEngine;
}

bool TextEngine::isCursorAtBottomOfView() const
{

    if ((*(*getVideoEngine()).getFrameBuffer()).getRow() == (*(*getVideoEngine()).getFrameBuffer()).getMaxRows() - 2)
    {
        return true;
    }
    return false;
}

bool TextEngine::isCursorAtEndOfViewLine() const
{
     VideoEngine *video = getVideoEngine();

    if ((*(*getVideoEngine()).getFrameBuffer()).getCol() == (*(*getVideoEngine()).getFrameBuffer()).getMaxCols() - 1)
    {
        return true;
    }
    return false;
}

void TextEngine::renderClearView()
{
   (*(*getVideoEngine()).getFrameBuffer())
        .clearScreen()
        .cursorMoveBegin();

}

void TextEngine::renderClearLine()
{
    (*(*getVideoEngine()).getFrameBuffer()).clearLine();
}

void TextEngine::renderLineBreak()
{
    if ((*getVideoEngine()->getFrameBuffer()).getRow() == ((*getVideoEngine()->getFrameBuffer()).getMaxRows() - 1))
    {
        (*(*getVideoEngine()).getFrameBuffer())
            .clearScreen()
            .cursorMoveBegin()
            .cursorMoveRight();
    } else {
        (*(*getVideoEngine()).getFrameBuffer())
            .cursorMoveDown()
            .clearLine()
            .cursorMoveStartOfLine()
            .cursorMoveRight();
    }
}

void TextEngine::renderCarriageReturn()
{
   (*(*getVideoEngine()).getFrameBuffer())
        .cursorMoveStartOfLine()
        .cursorMoveRight();
}

void TextEngine::renderCursor()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .write('|');
}

void TextEngine::renderTabulation()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .write(' ');
}

void TextEngine::renderLineOverflowIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), (*getVideoEngine()->getFrameBuffer()).getMaxCols() - 1)
        .fixedWrite('>');
}

void TextEngine::renderLineWithOverflowIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), 0)
        .fixedWrite('+');
}

void TextEngine::renderEmptyLineIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), 0)
        .fixedWrite('~');
}

void TextEngine::renderLineWithContentIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), 0)
        .fixedWrite('.');
}

void TextEngine::renderEOF()
{

}

void TextEngine::renderCharacter(DocCharacter *dc)
{
    if ((*dc).getChar() == '\0')
    {
        (*(*getVideoEngine()).getFrameBuffer())
            .write(' ');
    } else {
        (*(*getVideoEngine()).getFrameBuffer())
            .write((*dc).getChar());
    }
    cout << "[" << (*(*getVideoEngine()).getFrameBuffer()).getRow() << "," << (*(*getVideoEngine()).getFrameBuffer()).getCol() << "]" << endl;
}

void TextEngine::renderColRow(int row, int col, int bytes)
{
    char number_array[5 + sizeof(char)];

    (*(*getVideoEngine()).getFrameBuffer())
      .gotoXY((*(*getVideoEngine()).getFrameBuffer()).getMaxRows() - 1,(*(*getVideoEngine()).getFrameBuffer()).getMaxCols()-18);

    sprintf(number_array, "%d", (bytes)+10000);
    (*getVideoEngine()->getFrameBuffer())
        .write('(')
        .write(number_array[1])
        .write(number_array[2])
        .write(number_array[3])
        .write(number_array[4])
        .write(')')
        .write(' ');

    sprintf(number_array, "%d", (row)+1000);

    (*getVideoEngine()->getFrameBuffer())
        .write('[')
        .write(number_array[1])
        .write(number_array[2])
        .write(number_array[3]);

    sprintf(number_array, "%d", (col)+1000);

    (*getVideoEngine()->getFrameBuffer())
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

TextEngine::TextEngine(Document * document, VideoEngine *videoEngine):
DocumentEngine(document),
_videoEngine(videoEngine)
{

}



