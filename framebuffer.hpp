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
#ifndef FRAMEBUFFER
#define FRAMEBUFFER

#include "csa_object.hpp"

/*
    Controls logical visualization before show into a LCD, for instance
    controlling the viewport logic.
*/
class FrameBuffer: public CSAObject
{
    public:
        FrameBuffer(int, int);
        ~FrameBuffer();

        void setMaxRows(const int);
        int getMaxRows() const;
        void setMaxCols(const int);
        int getMaxCols() const;
        void setCol(const int);
        int getCol() const;
        void setRow(const int);
        int getRow() const;

        char * getScreenRow(const int) const;

        FrameBuffer & gotoXY(const int, const int);

        FrameBuffer & write(const char [], const int);
        FrameBuffer & write(const char);
        FrameBuffer & cursorMoveBegin();
        FrameBuffer & cursorMoveUp();
        FrameBuffer & cursorMoveDown();
        FrameBuffer & cursorMoveLeft();
        FrameBuffer & cursorMoveRight();
        FrameBuffer & cursorMoveEndOfLine();
        FrameBuffer & cursorMoveStartOfLine();
        FrameBuffer & clearScreen();
        FrameBuffer & clearLine();

        virtual void toString();
        virtual int getMemSize();

    private:
        int _maxRows;
        int _maxCols;
        int _row;
        int _col;
        char _screen[80][40];

        int getLineLength() const;
};

#endif // DOCUMENT
