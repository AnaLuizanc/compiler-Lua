#include "ComandoWhile.hpp"
#include "../debug-util.hpp"
#include <iostream>

using namespace std;

void ComandoWhile::debug_com_tab(int tab) {
    tab3(tab); cerr << "INI WHILE" << endl;
    
    tab3(tab + 1); cerr << "CONDICAO:" << endl;
    if (condicao != nullptr) condicao->debug_com_tab(tab + 2);
    
    tab3(tab + 1); cerr << "BLOCO:" << endl;
    for (Comando* cmd : bloco) {
        if (cmd != nullptr) cmd->debug_com_tab(tab + 2);
    }
    
    tab3(tab); cerr << "FIM WHILE" << endl;
}