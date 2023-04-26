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

int main()
{

    FrameBuffer fb(4,20);

    fb.toString();

    fb
        .write('O')
        .write('l')
        .write('a')
        .cursorMoveDown()
        .write(' ')
        .write(' ')
        .write(' ')
        .write('M')
        .write('u')
        .write('n')
        .write('d')
        .write('o');

    fb.toString();
    cout << "\nFinalizado!" << endl;

    return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}






