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
    char frase[] = {"\r\n\r\nLorem ipsum dolor sit amet, consectetur adipiscing elit. Sed suscipit neque id mi aliquet sodales. Duis at ullamcorper lacus. Nullam sed vehicula lacus. Sed pharetra urna interdum tortor tempor, sit amet pharetra felis gravida. Aliquam lacinia dui nec ligula consectetur laoreet. Duis venenatis, quam hendrerit porttitor consectetur, ligula mi viverra erat, nec gravida nulla turpis sit amet erat. Nam sit amet purus quis neque sodales semper ac porttitor eros. Phasellus pulvinar tristique sapien, nec tincidunt libero ultrices ut. Duis vel quam vel felis egestas tempus. Nam vitae arcu vel elit viverra fermentum. Suspendisse vehicula risus ut lectus ultrices luctus. Proin consequat odio ac tellus bibendum, sit amet molestie ligula vestibulum. Suspendisse ac sapien sit amet leo vestibulum laoreet. Mauris varius, arcu sit amet accumsan bibendum, nulla mauris varius ipsum, quis maximus dui libero posuere odio.\r\n\r\nAenean tincidunt enim sed condimentum porta. Nam eget dui id nisi sagittis congue ac sit amet augue. Suspendisse ornare maximus lectus, quis auctor ante elementum ac. Vivamus aliquet aliquet sapien, id volutpat mi faucibus a. Nam quis nibh maximus est bibendum hendrerit eget nec dolor. Integer eget metus eu elit posuere cursus at a risus. Duis bibendum magna lorem, non tempor elit accumsan sed. Praesent luctus ullamcorper purus eu scelerisque. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque facilisis, est sit amet ultricies interdum, mi velit porttitor augue, vel egestas justo neque et magna.\r\n\r\nMaecenas et lectus ut magna pharetra laoreet vitae ut ex. Maecenas eget arcu id diam facilisis pellentesque. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Pellentesque tristique nibh aliquet erat efficitur, in molestie leo rhoncus. Ut eu magna id sem auctor dignissim at ut nunc. Nullam vel diam neque. Maecenas quis erat ut metus egestas facilisis. Nulla facilisi.\r\n\r\nVestibulum tincidunt, risus vel sodales lobortis, ex tellus fringilla neque, et aliquet quam enim nec augue. Phasellus porta dui nisl, sed elementum justo ultricies ut. Nullam quis dui in diam ullamcorper blandit ut sed urna. Phasellus dictum, ex eu ultrices blandit, purus metus cursus lorem, in tristique odio massa quis mi. Vestibulum purus felis, sodales vitae enim et, scelerisque dignissim tortor. Phasellus consequat varius dolor, lobortis placerat nisi. Maecenas id nisi non elit aliquet malesuada. Cras bibendum efficitur congue.\r\n\r\nDuis molestie magna tempus eros egestas, sit amet lacinia nulla consequat. Morbi consequat velit ut sagittis pellentesque. Aenean id fringilla enim. Phasellus fringilla imperdiet erat euismod molestie. Pellentesque fringilla justo eget interdum pulvinar. Pellentesque justo massa, volutpat et gravida consectetur, bibendum a augue. In vestibulum arcu risus, ut tristique nisi vulputate nec. Etiam ac efficitur tellus. Donec tincidunt lacus nisi, eu lacinia felis placerat a. Pellentesque pellentesque justo eget lacus fermentum consequat. Morbi orci urna, molestie vitae placerat eu, malesuada sed lacus. Vivamus tincidunt porta nulla sit amet tempus.\r\n\r\nAenean ut cursus arcu, sed gravida elit. Integer sit amet euismod purus. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Donec quis lacinia diam. Nulla suscipit dictum magna eget sollicitudin. Mauris venenatis metus in placerat ultricies. Fusce nec iaculis ipsum. Nulla vestibulum libero et orci maximus sollicitudin. Vestibulum ullamcorper, nulla non efficitur pharetra, est elit finibus ligula, fringilla sagittis ante dui quis justo. Etiam a neque urna. Etiam nisl purus, pellentesque cursus suscipit in, tempor eget est.\r\n\r\nMauris sed leo sed justo varius lobortis. Morbi sed elit condimentum, volutpat magna ut, semper sapien. Mauris a tortor ante. Vestibulum facilisis metus tortor, eu convallis lectus posuere eu. Integer in sem sodales, maximus nisi ut, pellentesque velit. Curabitur placerat dolor non orci iaculis hendrerit. Morbi vel blandit mi. Morbi eu tristique velit. Duis molestie neque id lobortis molestie donec. "};

    AppGlobals::getInstance().setEnableObjDelLog(false);

    //Diferente do Java, quando nao tem parametros para passar no construtor (como () ),
    //da erro, tem que passar sem!
    DocRow linha1;
    linha1.fromCharArray(frase);

    cout << "Tamanho da linha em bytes: " << getMemSize(&linha1) << endl;

    TextEngine textEngine;
    textEngine.toString();

    cout << "\n---------------------------------------------" << endl;
    linha1.deleteAllChars();
    cout << "\nFinalizado!" << endl;

    return 0;
}


int getMemSize(CSAObject *obj)
{
    return obj->getMemSize();
}






