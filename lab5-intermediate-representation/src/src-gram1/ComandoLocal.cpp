#include "ComandoLocal.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ComandoLocal::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "[" << nome;
    if (tipo != NULL) 
        cerr << ":" << tipo->nome();
    
    cerr << "] Declaracao" << endl;
}