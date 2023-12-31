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
#ifndef CORECOLLECTION
#define CORECOLLECTION

#include "csa_object.hpp"

#include "core/document.hpp"
#include "core/text_render_engine.hpp"
#include "core/text_persistence_engine.hpp"
#include "core/open_file_menu.hpp"
#include "core/main_menu.hpp"
#include "core/new_file_menu.hpp"
#include "core/save_as_menu.hpp"
#include "core/line_zoom.hpp"
#include "core/about.hpp"

/*
  General resource holder to manager singletons about the app core instances
  Like BeanManager of Java Spring
*/
class CoreCollection : public CSAObject
{
public:

    ~CoreCollection();

    static CoreCollection & getInstance();

    Document * getCurrentDocument();
    TextRenderEngine * getTextRenderEngine();
    TextPersistenceEngine * getTextPersistenceEngine();
    OpenFileMenu * getOpenFileMenu();
    MainMenu * getMainMenu();
    NewFileMenu * getNewFileMenu();
    SaveAsMenu * getSaveAsMenu();
    LineZoom * getLineZoom();
    About * getAbout();

    void setCurrentDocument(Document *);
    void setTextRenderEngine(TextRenderEngine *);
    void setTextPersistenceEngine(TextPersistenceEngine *);
    void setOpenFileMenu(OpenFileMenu *);
    void setMainMenu(MainMenu *);
    void setNewFileMenu(NewFileMenu *);
    void setSaveAsMenu(SaveAsMenu *);
    void setLineZoom(LineZoom *);
    void setAbout(About *);

    virtual void toString(); // Yes, you know, Java feelings rs
    virtual int getMemSize();

private:
    CoreCollection();

    static CoreCollection* _me;

    OpenFileMenu * _openFileMenuPtr;
    TextPersistenceEngine * _textPersistenceEnginePtr;
    TextRenderEngine * _textRenderEnginePtr;
    Document * _currentDocumentPtr;
    MainMenu * _mainMenuPtr;
    NewFileMenu * _newFileMenuPtr;
    SaveAsMenu * _saveAsMenuPtr;
    LineZoom * _lineZoomPtr;
    About * _aboutPtr;

};

#endif // DOCCHARACTER

