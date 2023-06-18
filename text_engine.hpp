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
#ifndef TEXTENGINE
#define TEXTENGINE

#include "document_engine.hpp"
#include "document.hpp"
#include "video_engine.hpp"
#include "keyboard_engine.hpp"
#include "widget_callback.hpp"

/*
  The abstract document engine processing
*/
class TextEngine : public DocumentEngine
{
    public:
        TextEngine(Document *, VideoEngine *);
        ~TextEngine();

        virtual bool isCursorAtEndOfViewLine() const;
        virtual bool isCursorAtBottomOfView() const;

        virtual void renderClearView();
        virtual void renderClearLine();
        virtual void renderLineBreak();
        virtual void renderCarriageReturn();
        virtual void renderCursor();
        virtual void renderTabulation();
        virtual void renderLineOverflowIndicator();
        virtual void renderLineWithOverflowIndicator();
        virtual void renderEmptyLineIndicator();
        virtual void renderLineWithContentIndicator();
        virtual void renderEOF();
        virtual void renderCharacter(DocCharacter *);
        virtual void renderColRow(int, int, int);

        virtual VideoEngine * getVideoEngine() const;

        virtual void toString(); // Yes, you know, Java feelings rs
        virtual int getMemSize();

        virtual void run(VideoEngine *, KeyboardEngine *);

    private:

        WidgetCallback* _widgetCallback;
        VideoEngine *_videoEngine;
};

#endif // DOCCHARACTER



