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

    doc.type({"Ola, essa e a linha 1"});
    (*doc.getCurrentRowPtr()).readAllChars();
    cout << endl;


    doc.cursorMoveStartOfLine().cursorMoveRight().cursorMoveRight().cursorMoveRight().cursorMoveRight();
    doc.triggerBackspace().triggerBackspace();
    (*doc.getCurrentRowPtr()).readAllChars();
    cout << endl;



    cout << "\nFinalizado!" << endl;

    return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}






