#include "ExpressaoUnaria.hpp"
#include <iostream>
#include "../debug-util.hpp"

void ExpressaoUnaria::debug_com_tab(int tab) {
    tab3(tab);
    cerr << simbolo << " [ INI " << nome_op << endl;
    
    if (expressao != nullptr) expressao->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << " ] FIM " << nome_op << endl;
}