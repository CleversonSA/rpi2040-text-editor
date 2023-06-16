
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

#include "framebuffer.hpp"
#include "app_globals.hpp"

FrameBuffer & FrameBuffer::fixedWrite(const char character)
{
    _screen[_row][_col] = character;
    return (*this);
}

bool FrameBuffer::isAtBottom() const
{
    return (getRow() == getMaxRows());
}

bool FrameBuffer::isAtTop() const
{
    return (getRow() == 0);
}

bool FrameBuffer::isAtStartOfLine() const
{
    return (getCol() == 0);
}

bool FrameBuffer::isAtEndOfLine() const
{
    return (getCol() == getMaxCols());
}

char * FrameBuffer::getScreenRow(const int row) const
{
    char * charCols = new char[getMaxCols()];

    for (int i=0; i<_maxCols; i++)
    {
        (*charCols) = _screen[row][i];
        charCols++;
    }

    charCols = charCols - (_maxCols);

    return charCols;
}


FrameBuffer & FrameBuffer::clearLine()
{
    for (int i=0; i<_maxCols ; i++)
    {
        _screen[_row][i] = '\0';
    }

    return (*this);
}

FrameBuffer & FrameBuffer::clearScreen()
{
    for (int i=0; i<_maxCols ; i++)
    {
        for(int j=0; j<_maxRows ; j++)
        {
            _screen[j][i] = '\0';
        }
    }

    return (*this);
}

FrameBuffer & FrameBuffer::cursorMoveBegin()
{
    setCol(0);
    setRow(0);

    return (*this);
}

FrameBuffer & FrameBuffer::cursorMoveDown()
{
    setCol(0);
    setRow(getRow()+1);

    if (getRow() > (getMaxRows() - 1))
    {
        setRow((getMaxRows() - 1));
    }

    return (*this);
}

int FrameBuffer::getLineLength() const
{
    int itemCount = 0;

    for (int i = 0; i<_maxCols; i++)
    {
        if (_screen[_row][i] == '\0')
            return itemCount + 1;
        itemCount++;
    }

    return 0;
}


FrameBuffer & FrameBuffer::cursorMoveEndOfLine()
{
    int qtItems = getLineLength();
    if (qtItems > 0)
    {
        setCol(getLineLength() - 1);
    } else {
        setCol(0);
    }

    return (*this);
}

FrameBuffer & FrameBuffer::cursorMoveLeft()
{
    setCol(getCol() - 1);

    if (getCol() < 0)
    {
        cursorMoveUp();
        cursorMoveEndOfLine();
    }

    return (*this);
}

FrameBuffer & FrameBuffer::cursorMoveStartOfLine()
{
    setCol(0);

    return (*this);
}

FrameBuffer & FrameBuffer::cursorMoveRight()
{
    setCol(getCol() + 1);

    if (getCol() >= getMaxCols())
    {
        cursorMoveDown();
        cursorMoveStartOfLine();
    }

    return (*this);
}

FrameBuffer & FrameBuffer::cursorMoveUp()
{
    setRow(getRow() -1 );

    if (getRow() < 0)
    {
        setRow(0);
        setCol(0);
    } else {
        cursorMoveEndOfLine();
    }

    return (*this);
}

FrameBuffer & FrameBuffer::gotoXY(const int row, const int col)
{
    if (row <= 0) {
        setRow(0);
    } else if (row >= getMaxRows()) {
        setRow(getMaxRows() - 1);
    } else {
        setRow(row);
    }

    if (col < 0) {
        setCol(0);
    } else if (col >= getMaxCols()) {
        setCol(getMaxCols() - 1);
    } else {
        setCol(col);
    }

    return (*this);
}

FrameBuffer & FrameBuffer::write(const char characters[], const int len)
{
    for (int i=0; i<len; i++){
        write(characters[i]);
    }

    return (*this);
}

FrameBuffer & FrameBuffer::write(const char character)
{
   _screen[getRow()][getCol()] = character;
   cursorMoveRight();

   return (*this);
}

int FrameBuffer::getRow() const
{
    return _row;
}

int FrameBuffer::getCol() const
{
    return _col;
}

void FrameBuffer::setRow(const int row)
{
    _row = row;
}

void FrameBuffer::setCol(const int col)
{
    _col = col;
}

void FrameBuffer::setMaxRows(const int maxRows)
{
    _maxRows = maxRows;
}


int FrameBuffer::getMaxRows() const
{
    return _maxRows;
}


void FrameBuffer::setMaxCols(const int maxCols)
{
    _maxCols = maxCols;
}


int FrameBuffer::getMaxCols() const
{
    return _maxCols;
}

int FrameBuffer::getScreenRowChecksum(int row) const
{
    return _screenRowsChecksum[row];
}

FrameBuffer & FrameBuffer::updateScreenRowChecksum(int row)
{
    char *screenRow = _screen[row];

    _screenRowsChecksum[row] = AppGlobals::getInstance().calculateSimpleChecksum(screenRow, _maxCols);

    return (*this);
}

int FrameBuffer::calculateScreenRowChecksum(int row)
{
    return AppGlobals::getInstance().calculateSimpleChecksum(_screen[row], _maxCols);
}

void FrameBuffer::toString()
{
    cout << "[FrameBuffer] [UID=" << CSAObject::getSerialVersionUID() << "] [SIZE=" << sizeof((*this)) <<"] "
         << "[maxCols=" << getMaxCols() << "] "
         << "[maxRows=" << getMaxRows() << "] "
         << "[row=" << getRow() << "] "
         << "[col=" << getCol() << "] "
         << "[screen=";
         for (int i=0; i<_maxRows; i++)
         {
             for (int j=0; j<_maxCols; j++)
             {
                 cout << _screen[i][j];
             }
             cout << "|";
         }
         cout << "]" << endl;
}

int FrameBuffer::getMemSize()
{
    return sizeof((*this));
}

FrameBuffer::~FrameBuffer()
{
    if(AppGlobals::getInstance().getEnableObjDelLog() == true) {
        cout << "[FrameBuffer] [destUID=" << CSAObject::getSerialVersionUID() << "]" << endl;
    }
}

FrameBuffer::FrameBuffer(int maxRows, int maxCols):
CSAObject(),
_maxCols(maxCols),
_maxRows(maxRows),
_row(0),
_col(0)
{
    clearScreen();
}



