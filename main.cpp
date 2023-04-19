#include <iostream>
using std::cout;
using std::endl;

#include <cstring>
using std::strlen;

#include "doc_character.hpp"
#include "doc_row.hpp"

void readAllChars (const DocCharacter *);
int calculateSize (const DocCharacter *);
void deleteAllChars (const DocCharacter *);
void fromCharArray (const char [], DocRow &);

int main()
{
    char frase[] = {'O','l','a',' ','m','u','n','d','o','!',' ','S','a','l','u','t','o','n',' ','m','o','n','d','o','!','\0'};

    //Diferente do Java, quando nao tem parametros para passar no construtor (como () ),
    //da erro, tem que passar sem!
    DocRow linha1;
    DocCharacter * currentCharPtr = 0;

    fromCharArray(frase, linha1);

    cout << "Primeiro char " << (*linha1.getStartCharPtr()).getChar() << " Tamanho: " << sizeof((*linha1.getStartCharPtr())) << " byte(s)" << endl;
    cout << "Frase: ";
    readAllChars(linha1.getStartCharPtr());
    cout << endl;

    cout << "\nTamanho da frase para " << strlen(frase) << " letra(s): " <<
         calculateSize(linha1.getStartCharPtr())
         << " byte(s) \n" << endl;

    cout << "Retornando o 9 caracter da lista:" << endl;
        currentCharPtr = linha1.charPtrAt(0);
        (*currentCharPtr).toString();

    cout << "Modificando frase" << endl;
        (*currentCharPtr).setChar('#');
        readAllChars(linha1.getStartCharPtr());
    cout << endl;

    cout << "Vamos incrementar" << endl;
        DocCharacter dcz('Z');
        DocCharacter dca('a');
        DocCharacter dcb('b');
        DocCharacter dcu('u');
        DocCharacter dcm('m');
        DocCharacter dcb2('b');
        DocCharacter a2('a');

        linha1.append(&dcz).append(&dca).append(&dcb).append(&dcu).append(&dcm).append(&dcb2).append(&a2);
        readAllChars(linha1.getStartCharPtr());
    cout << endl;

    cout << "Vamos apagar:" << endl;
        linha1.deletePtrAt(0).deletePtrAt(9).deletePtrAt(10);
        readAllChars(linha1.getStartCharPtr());
    cout << endl;

    cout << "\n---------------------------------------------" << endl;
    deleteAllChars(linha1.getStartCharPtr());
    cout << "\nFinalizado!" << endl;

    return 0;
}

void fromCharArray(const char charArray [], DocRow &docRow)
{
    DocCharacter *startRowPtr = 0;
    DocCharacter *dc = 0;
    DocCharacter *previousPtr = 0;

    for (int i = 0; i<strlen(charArray)+1; i++) {
        dc = new DocCharacter(charArray[i]);

        if (startRowPtr == 0) {
            startRowPtr = dc;
        } else {
            (*previousPtr).setNextCharPtr(dc);
            (*dc).setPreviousCharPtr(previousPtr);
        }
        previousPtr = dc;
    }

    docRow.setStartCharPtr(startRowPtr);
}

int calculateSize (const DocCharacter * startCharPtr)
{
    static int fuse = 10000;
    int total = 0;

    fuse--;
    if (fuse < 0)
        return 0;

    if (startCharPtr != 0) {
        total = sizeof((*startCharPtr));
    } else {
        fuse = 10000;
        return total;
    }

    return total + calculateSize((*startCharPtr).getNextCharPtr());
}

void readAllChars (const DocCharacter * startCharPtr)
{
    static int fuse = 10000;

    fuse--;
    if (fuse < 0)
        return;

    if (startCharPtr != 0) {
        if ((*startCharPtr).getChar() != '\0')
        {
            cout << (*startCharPtr).getChar();
        }
    } else {
        fuse = 10000;
        return;
    }

    readAllChars((*startCharPtr).getNextCharPtr());
}


void deleteAllChars (const DocCharacter * startCharPtr)
{
    static int fuse = 10000;

    fuse--;
    if (fuse < 0)
        return;

    if (startCharPtr != 0) {
        deleteAllChars((*startCharPtr).getNextCharPtr());
        delete startCharPtr;
    } else {
        fuse = 10000;
        return;
    }

}
