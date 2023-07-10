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

#include "text_render_engine.hpp"
#include "engine/video_engine.hpp"
#include "engine/keyboard_engine.hpp"
#include "text_render_engine_keyboard_callback.hpp"


void TextRenderEngine::run(VideoEngine *videoEngine, KeyboardEngine *keyboardEngine)
{
    render();

    (*videoEngine).display(TextRenderEngine::DISPLAY_CONTEXT_ID);

    TextRenderEngineKeyboardCallback *kcb = new TextRenderEngineKeyboardCallback;

    (*kcb).setVideoEngine(videoEngine);
    (*kcb).setTextEngine(this);

    (*keyboardEngine).setup();
    (*keyboardEngine).setCallback(kcb);
    (*keyboardEngine).loop();

    delete kcb;
}


VideoEngine * TextRenderEngine::getVideoEngine() const
{
    return _videoEngine;
}

bool TextRenderEngine::isCursorAtBottomOfView() const
{

    if ((*(*getVideoEngine()).getFrameBuffer()).getRow() == (*(*getVideoEngine()).getFrameBuffer()).getMaxRows() - 1)
    {
        return true;
    }
    return false;
}

bool TextRenderEngine::isCursorAtEndOfViewLine() const
{
     VideoEngine *video = getVideoEngine();

    if ((*(*getVideoEngine()).getFrameBuffer()).getCol() == (*(*getVideoEngine()).getFrameBuffer()).getMaxCols() - 1)
    {
        return true;
    }
    return false;
}

void TextRenderEngine::renderClearView()
{
   (*(*getVideoEngine()).getFrameBuffer())
        .clearScreen()
        .cursorMoveBegin();

}

void TextRenderEngine::renderClearLine()
{
    (*(*getVideoEngine()).getFrameBuffer()).clearLine();
}

void TextRenderEngine::renderLineBreak()
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

void TextRenderEngine::renderCarriageReturn()
{
   (*(*getVideoEngine()).getFrameBuffer())
        .cursorMoveStartOfLine()
        .cursorMoveRight();
}

void TextRenderEngine::renderCursor()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .write('|');
}

void TextRenderEngine::renderTabulation()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .write(' ');
}

void TextRenderEngine::renderLineOverflowIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), (*getVideoEngine()->getFrameBuffer()).getMaxCols() - 1)
        .fixedWrite('>');
}

void TextRenderEngine::renderLineWithOverflowIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), 0)
        .fixedWrite('+');
}

void TextRenderEngine::renderEmptyLineIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), 0)
        .fixedWrite('~');
}

void TextRenderEngine::renderLineWithContentIndicator()
{
    (*(*getVideoEngine()).getFrameBuffer())
        .gotoXY((*getVideoEngine()->getFrameBuffer()).getRow(), 0)
        .fixedWrite('.');
}

void TextRenderEngine::renderEOF()
{

}

void TextRenderEngine::renderCharacter(DocCharacter *dc)
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

void TextRenderEngine::renderColRow(int row, int col, int bytes)
{
    char number_array[5 + sizeof(char)];

    (*(*getVideoEngine()).getFrameBuffer())
      .gotoXY((*(*getVideoEngine()).getFrameBuffer()).getMaxRows()-1,(*(*getVideoEngine()).getFrameBuffer()).getMaxCols()-10);

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

void TextRenderEngine::toString()
{
    cout << "[TextEngine] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << endl;
}

int TextRenderEngine::getMemSize()
{
    return sizeof((*this));
}

TextRenderEngine::~TextRenderEngine()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[TextRenderEngine] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

TextRenderEngine::TextRenderEngine(Document * document, VideoEngine *videoEngine):
DocumentEngine(document),
_videoEngine(videoEngine)
{

}



