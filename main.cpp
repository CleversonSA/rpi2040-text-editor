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

int getMemSize(CSAObject *);

int main()
{
    //Document doc;

    DocRow linha;

    linha.append('o').append('l').append('a');

    linha.readAllChars();
    cout << endl;

    //doc.type({"Olá, essa é a linha 1\nAgora é a linha 2\nAgora é a linha 3\nAgora é a linha 4\0"});
    //doc.cursorMoveUp().cursorMoveUp().cursorMoveUp().cursorMoveUp();
    //(*doc.getCurrentRowPtr()).readAllChars();
    cout << "\nFinalizado!" << endl;

    return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}






