#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
using std::strlen;

#include "csa_object.hpp"
#include "doc_character.hpp"
#include "doc_row.hpp"
#include "app_globals.hpp"

int getMemSize(CSAObject *);

int main()
{
    char frase[] = {'O','l','a',' ','m','u','n','d','o','!',' ','S','a','l','u','t','o','n',' ','m','o','n','d','o','!','\0'};

    AppGlobals::getInstance().setEnableObjDelLog(false);

    //Diferente do Java, quando nao tem parametros para passar no construtor (como () ),
    //da erro, tem que passar sem!
    DocRow linha1;
    DocCharacter * currentCharPtr = 0;

    linha1.fromCharArray(frase);

    cout << "Primeiro char " << (*linha1.getStartCharPtr()).getChar() << " Tamanho: " << getMemSize(linha1.getStartCharPtr()) << " byte(s)" << endl;
    cout << "Frase: ";
    linha1.readAllChars();
    cout << endl;

    cout << "\nTamanho da frase para " << strlen(frase) << " letra(s): " <<
         linha1.getSize()
         << " byte(s) \n" << endl;

    cout << "Retornando o 9 caracter da lista:" << endl;
        currentCharPtr = linha1.charPtrAt(0);
        (*currentCharPtr).toString();

    cout << "Modificando frase" << endl;
        (*currentCharPtr).setChar('#');
        linha1.readAllChars();
    cout << endl;

    cout << "Vamos incrementar" << endl;
        linha1.append({"Zabumba"}).append({" é o que ha!"});
        linha1.readAllChars();
    cout << endl;

    cout << "Vamos apagar:" << endl;
        linha1.deletePtrAt(0).deletePtrAt(9).deletePtrAt(10);
        linha1.readAllChars();
    cout << endl;

    cout << "Vamos incrementar no meio:" << endl;
        linha1.append({"-- Olha eu aqui --"}, 10);
        linha1.readAllChars();
    cout << endl;

    cout << "Tamanho da linha em bytes:" << getMemSize(&linha1) << endl;

    cout << "\n---------------------------------------------" << endl;
    linha1.deleteAllChars();
    cout << "\nFinalizado!" << endl;

    return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}






