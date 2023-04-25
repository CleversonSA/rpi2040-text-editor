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
    Document doc;

    doc.type({"Ola, essa e a linha 1!\nAqui está a linha 2"});

    doc
        .cursorMoveUp()
        .cursorMoveUp();
    (*doc.getCurrentRowPtr()).readAllChars();
    cout << endl;

    doc
        .cursorMoveDown()
        .cursorMoveStartOfLine()
        .triggerBackspace();
    (*doc.getCurrentRowPtr()).readAllChars();
    cout << endl;

    doc
        .cursorMoveEndLine()
        .addNewLine()
        .type({"Tem mais lixo aqui embaixo na linha 2!"})
        .addNewLine()
        .type({"E aqui na linha 3 tambem"})
        .cursorMoveUp()
        .cursorMoveStartOfLine()
        .triggerBackspace()
        .triggerBackspace();
    (*doc.getCurrentRowPtr()).readAllChars();
    cout << endl;

    doc
        .cursorMoveDown();
    (*doc.getCurrentRowPtr()).readAllChars();
    cout << endl;

    cout << "\nFinalizado!" << endl;

    return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}






