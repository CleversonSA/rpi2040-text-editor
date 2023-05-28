#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <cstring>
using std::strlen;
using std::strtok;

#include "csa_object.hpp"
#include "doc_character.hpp"
#include "doc_row.hpp"
#include "app_globals.hpp"
#include "document.hpp"
#include "framebuffer.hpp"

#include "text_engine.hpp"
#include "msgbox_engine.hpp"
#include "inputbox_engine.hpp"
#include "splashbox_engine.hpp"
#include "menu_engine.hpp"
#include "textview_engine.hpp"

#include "lcd4x20_msgbox.hpp"
#include "lcd4x20_inputbox.hpp"
#include "lcd4x20_splashbox.hpp"
#include "lcd4x20_menu.hpp"
#include "lcd4x20_textview.hpp"

int getMemSize(CSAObject *);
void frameBufferToConsole(FrameBuffer *fb);
void handleMsgBoxButton(const int);
void handleInputBox(const int, char *);
void handleMenuItem(char *, char *);
void handleSplashBox(void);
void handleView(void);

int main()
{
    int pausa = 0;
    FrameBuffer fb(4,20);
    FrameBuffer fbMsgbox(4,20);
    FrameBuffer fbInputbox(4,20);
    FrameBuffer fbSplashBox(4,20);
    FrameBuffer fbMenu(4,20);
    FrameBuffer fbTextView(4,20);

    LCD4X20MsgBox lcd4x20msgbox(&fbMsgbox);
    LCD4X20InputBox lcd4x20inputbox(&fbInputbox);
    LCD4X20Splashbox lcd4x20splashbox(&fbSplashBox);
    LCD4X20Menu lcd4x20menu(&fbMenu);

    MsgBoxEngine *msgbox = &lcd4x20msgbox;
    InputBoxEngine *inputbox = &lcd4x20inputbox;
    SplashBoxEngine *splashbox = &lcd4x20splashbox;
    MenuEngine *menu = &lcd4x20menu;

    LCD4X20TextView lcd4x20textview(&fbTextView, menu);
    TextViewEngine *textView = &lcd4x20textview;


    cout << "Inicializado" << endl;

    /*Document doc;
    TextEngine textEngine(&doc, &fb);


    doc
        .type({"Lorem ipsum dolor sit amet\nconsectetur adipiscing elit.\n"})
        .type({"Etiam ut ligula ante. In nec ante velit.\n Sed convallis volutpat lectus sit amet ultrices. Praesent eu interdum mi.\n"})
        .type({"Quisque varius\n congue finibus.\n Etiam et nisl\n sagittis, sollicitudin\n eros id, cursus turpis.\n Morbi consequat \n"})
        .type({"quis nisl sed posuere. Sed eu euismod justo. Phasellus lectus tortor, porttitor a bibendum non, venenatis eget lacus. Duis a neque a nunc pulvinar volutpat et non purus. Morbi tempus condimentum dolor non luctus. Maecenas tristique pharetra nibh laoreet porta. Cras sodales varius risus eget volutpat. Morbi rhoncus mollis nulla, vel ultricies lacus posuere et."})
        .type({"In efficitur metus nisl, quis consectetur ipsum fringilla a.\n Integer faucibus elementum sapien, vel\n ultrices ipsum hendrerit \n"})
        .type({"eget. In vitae mattis lectus. Proin id est egestas lorem faucibus aliquet.\n"})
        .type({"Sed placerat molestie orci, nec mollis velit cursus tempor. "});

    doc
        .cursorMoveBegin();

    textEngine.render();
    */

    /*(*msgbox)
        .reset()
        .setTitle({"Greetings"})
        .setMessage({"What do you think?"})
        .setButtonType(MsgBoxEngine::YESNOCANCEL_BUTTON)
        .setIconType(MsgBoxEngine::QUESTION_ICON)
        .setCallbackfn(&handleMsgBoxButton)
        .render();

    frameBufferToConsole(&fbMsgbox);

    cin >> pausa;
    (*msgbox)
        .cursorMoveNextButton()
        .render();
    frameBufferToConsole(&fbMsgbox);

    cin >> pausa;
    (*msgbox)
        .cursorMoveNextButton()
        .render();
    frameBufferToConsole(&fbMsgbox);

    cin >> pausa;
    (*msgbox)
        .cursorMovePreviousButton()
        .render();
    frameBufferToConsole(&fbMsgbox);

    cin >> pausa;
    (*msgbox)
        .cursorMovePreviousButton()
        .render();

    frameBufferToConsole(&fbMsgbox);

    (*msgbox)
        .selectButton();

    cout << "\nFinalizado!" << endl;



    (*inputbox)
        .reset()
        .setTitle({"Save As"})
        .setMessage({"Enter file name:"})
        .render();

    frameBufferToConsole(&fbInputbox);

    cin >> pausa;

    (*inputbox)
        .type('O')
        .type('l')
        .type('a')
        .type('.')
        .type('t')
        .type('x')
        .type('t')
        .triggerBackspace()
        .triggerBackspace()
        .triggerBackspace()
        .triggerBackspace()
        .triggerBackspace()
        .triggerBackspace()
        .triggerBackspace()
        .triggerBackspace()
        .type('O')
        .type('l')
        .type('a')
        .type('.')
        .type('t')
        .type('x')
        .type('t')
        .setCallbackfn(&handleInputBox)
        .render();

    frameBufferToConsole(&fbInputbox);

    (*inputbox)
        .triggerESC();
*/
   /* (*splashbox)
        .reset()
        .setTitle({"Saving..."})
        .setMessage({"Wait for file saving, be patient!"})
        .setIconType(SplashBoxEngine::NO_ICON)
        .setCallbackfn(&handleSplashBox)
        .render();

    frameBufferToConsole(&fbSplashBox);

    cin >> pausa;

    (*splashbox)
        .hide();
*/

    /*char str[] = "NEW_FILE;New File|OPEN_FILE;Open File...|SAVE;Save file|SAVE_AS;Save as|SEPARATOR;Separator|INFO;Information|RESTART;Restart|ABOUT;About|EXIT;exit|ITEM1;item1|ITEM2;item2";
	char delim[] = "|";

	char *ptr = strtok(str, delim);
    char *itemPtr[100];
    int itemPos = 0;
    int qtItems = 0;
    int selectedItemPos = 8;

	while(ptr != 0)
	{
        itemPtr[itemPos] = ptr;

		cout << "Token: " << ptr << endl;
        ptr = strtok(0, delim);
        itemPos++;
        qtItems++;
	}

	itemPos = 0;
	char *itemDetailPtr = 0;
	bool lastPage = false;
	while (itemPos < qtItems)
    {
        if (selectedItemPos >= itemPos) {
            lastPage = false;
        } else {
            lastPage = true;
        }

        if (((itemPos % 4) == 0) && !lastPage) {
            system("cls");
        } else if (((itemPos % 4) == 0) && lastPage){
            break;
        }

        if (itemPos == selectedItemPos) {
            cout << ">> ";
        }

        itemDetailPtr = strtok(itemPtr[itemPos], {";"});
        cout << "Value:" <<  itemDetailPtr << " - ";

        itemDetailPtr= strtok(0, {";"});
        cout << "Label:" <<  itemDetailPtr;

        if (itemPos == selectedItemPos) {
            cout << "<< ";
        }

        cout << endl;

        itemDetailPtr = 0;
        itemPos++;
    }*/

    /* That´s new to me. If I use parseString("some str"), tokinzer will fail. I have to materialize a char array in order to strtok recoginze it! o.O */
    /*char menuString[] = "NEW_FILE;New File|OPEN_FILE;Open File...|SAVE;Save file|SAVE_AS;Save as|SEPARATOR;Separator|INFO;Information|RESTART;Restart|ABOUT;About|EXIT;exit|ITEM1;item1|ITEM2;item2";
    char newFileSubmenuString[] = "EMPTY_DOC;Empty document|TEMPLATE_DOC;Template document|BACK;Back";

    (*menu)
        .reset()
        .setTitle("Main menu")
        .parseMenuString(menuString)
        .setCallbackfn(&handleMenuItem)
        .render();

    frameBufferToConsole(&fbMenu);

    pausa = 0;
    cin >> pausa;

    (*menu)
        .reset()
        .setTitle("New file")
        .parseMenuString(newFileSubmenuString)
        .setCallbackfn(&handleMenuItem)
        .render();

    pausa= 0;
    frameBufferToConsole(&fbMenu);
    cin >> pausa;


    (*menu)
        .cursorMoveUp()
        .render();

    pausa= 0;
    frameBufferToConsole(&fbMenu);
    cin >> pausa;

    (*menu)
        .cursorMoveUp()
        .render();

    pausa= 0;
    frameBufferToConsole(&fbMenu);
    cin >> pausa;


    (*menu)
        .reset()
        .setTitle("Main menu")
        .parseMenuString(menuString)
        .setCallbackfn(&handleMenuItem)
        .render();

    frameBufferToConsole(&fbMenu);

    pausa = 0;
    cin >> pausa;

    (*menu)
        .selectItem();
*/

    char text[] = "Lorem ipsum dolor\nconsectetur adipiscing elit.\n Suspendisse quis\n ullamcorper enim.\n Mauris placerat \ncommodo efficitur. \nPhasellus pharetra, sem \nid viverra \naliquet, orci \nante vehicula ex, vestibulum \nconsequat erat metus\n quis tortor. Sed ac\n fina.";
    (*textView)
        .reset()
        .setTitle("History")
        .parseViewString(text)
        .setCallbackfn(&handleView)
        .render();

    frameBufferToConsole(&fbTextView);

    pausa = 0;
    cin >> pausa;

    (*textView)
        .cursorMoveUp()
        .render();

    pausa= 0;
    frameBufferToConsole(&fbTextView);
    cin >> pausa;

    (*textView)
        .closeView();

    pausa= 0;
    cin >> pausa;


	return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}

void frameBufferToConsole(FrameBuffer *fb)
{
    char * screenLine = 0;

    system("cls");
    for (int i=0; i < (*fb).getMaxRows(); i++)
    {
        screenLine = (*fb).getScreenRow(i);
        for (int j=0; j < (*fb).getMaxCols(); j++)
        {
            if ((*screenLine) == '\0')
            {
                cout << " ";
            } else {
                cout << (*screenLine);
            }
            screenLine++;
        }
        cout << endl;
    }
}


void handleMsgBoxButton(const int selectedButton)
{
    switch(selectedButton)
    {
    case(MsgBoxEngine::BTN_YES):
        cout << "!!!! VOCE ESCOLHEU O BOTAO SIM !!!!" << endl;
        break;
    case(MsgBoxEngine::BTN_NO):
        cout << "!!!! VOCE ESCOLHEU O BOTAO NAO !!!!" << endl;
        break;
    case(MsgBoxEngine::BTN_CANCEL):
        cout << "!!!! VOCE ESCOLHEU O BOTAO CANCELAR !!!!" << endl;
        break;
    default:
        cout << "!!!! VOCE ESCOLHEU O BOTAO OK !!!!" << endl;
        break;
    }
}


void handleInputBox(const int actionInput, char * userInput)
{
    if (actionInput == InputBoxEngine::CANCEL_TRIGGERED)
    {
        cout << "O USUÁRIO CANCELOU A ENTRADA!" << endl;
        return;
    }

    if (actionInput == InputBoxEngine::OK_TRIGGERED)
    {
        cout << "O usuário digitou:" << userInput << endl;
    }

}

void handleSplashBox(void)
{
    cout << "A JANELA FOI ENCERRADA!" << endl;

}

void handleMenuItem(char * value, char * label)
{
    cout << "A opcao selecionada foi:" << label << "(" << value << ")" << endl;
}


void handleView(void) {
    cout << "Saindo da tela" << endl;
}
