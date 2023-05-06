#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <cstring>
using std::strlen;

#include "csa_object.hpp"
#include "doc_character.hpp"
#include "doc_row.hpp"
#include "app_globals.hpp"
#include "document.hpp"
#include "text_engine.hpp"
#include "framebuffer.hpp"
#include "text_engine.hpp"

#include "menu_item.hpp"
#include "main_menu_new_file.hpp"

#include "msgbox_engine.hpp"
#include "lcd4x20_msgbox.hpp"

#include "inputbox_engine.hpp"
#include "lcd4x20_inputbox.hpp"

int getMemSize(CSAObject *);
void frameBufferToConsole(FrameBuffer *fb);
void triggerHandle(MenuItem *);
void handleMsgBoxButton(const int);
void handleInputBox(const int, char *);

int main()
{
    int pausa = 0;
    FrameBuffer fb(4,20);
    FrameBuffer fbMsgbox(4,20);
    FrameBuffer fbInputbox(4,20);

    LCD4X20MsgBox lcd4x20msgbox(&fbMsgbox);
    LCD4X20InputBox lcd4x20inputbox(&fbInputbox);

    MsgBoxEngine *msgbox = &lcd4x20msgbox;
    InputBoxEngine *inputbox = &lcd4x20inputbox;

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

    */

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
        .render();

    frameBufferToConsole(&fbInputbox);

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

void triggerHandle(MenuItem * menuItem)
{
    (*menuItem).handle();
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

