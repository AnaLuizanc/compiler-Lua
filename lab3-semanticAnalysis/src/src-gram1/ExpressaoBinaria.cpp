#include "ExpressaoBinaria.hpp"
#include <iostream>
#include "../debug-util.hpp"

void ExpressaoBinaria::debug_com_tab(int tab) {
    tab3(tab);
    cerr << simbolo << " [ INI " << nome_op << endl;
    
    if (esquerda != nullptr) esquerda->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << endl;
    
    if (direita != nullptr) direita->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << " ] FIM " << nome_op << endl;
}