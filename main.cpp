#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
using std::strlen;

#include "csa_object.hpp"
#include "doc_character.hpp"
#include "doc_row.hpp"
#include "app_globals.hpp"
#include "document.hpp"
#include "text_engine.hpp"
#include "framebuffer.hpp"

int getMemSize(CSAObject *);
void frameBufferToConsole(FrameBuffer *fb);

int main()
{

    system("cls");

    char l1[21] = {"+------------------+"};
    char l2[21] = {"|                  |"};
    char l3[21] = {"|  Abestado!!!     |"};
    char l4[21] = {"+------------------+"};

    FrameBuffer fb(4,20);

    fb.toString();

    fb
        .write(l1, 20)
        .write(l2, 20)
        .write(l3, 20)
        .write(l4, 20)
        .gotoXY(0,2)
        .write({":)"}, 2);

    frameBufferToConsole(&fb);

    cout << "\nFinalizado!" << endl;

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
                cout << ".";
            } else {
                cout << (*screenLine);
            }
            screenLine++;
        }
        cout << endl;
    }
}




