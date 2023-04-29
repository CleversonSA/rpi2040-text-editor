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
#include "text_engine.hpp"

int getMemSize(CSAObject *);
void frameBufferToConsole(FrameBuffer *fb);

int main()
{

    //system("cls");

    FrameBuffer fb(4,20);
    Document doc;
    TextEngine textEngine(&doc, &fb);

    doc
        .type({"Lorem ipsum dolor sit amet\nconsectetur adipiscing elit.\n\n\n"})
        .type({"Etiam ut ligula ante. In nec ante velit.\n Sed convallis volutpat lectus sit amet ultrices. Praesent eu interdum mi.\n"})
        .type({"Quisque varius\n congue finibus.\n Etiam et nisl\n sagittis, sollicitudin\n eros id, cursus turpis.\n Morbi consequat \n"})
        .type({"quis nisl sed posuere. Sed eu euismod justo. Phasellus lectus tortor, porttitor a bibendum non, venenatis eget lacus. Duis a neque a nunc pulvinar volutpat et non purus. Morbi tempus condimentum dolor non luctus. Maecenas tristique pharetra nibh laoreet porta. Cras sodales varius risus eget volutpat. Morbi rhoncus mollis nulla, vel ultricies lacus posuere et."})
        .type({"In efficitur metus nisl, quis consectetur ipsum fringilla a.\n Integer faucibus elementum sapien, vel\n ultrices ipsum hendrerit \n"})
        .type({"eget. In vitae mattis lectus. Proin id est egestas lorem faucibus aliquet.\n"})
        .type({"Sed placerat molestie orci, nec mollis velit cursus tempor. "});

    doc.cursorMoveBegin();
    textEngine.render();

    //frameBufferToConsole(&fb);

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




