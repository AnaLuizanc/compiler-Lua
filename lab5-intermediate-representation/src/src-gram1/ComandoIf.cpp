#include "ComandoIf.hpp"
#include "../debug-util.hpp"
#include <iostream>
#include "../Tree/Stm.hpp"

using namespace std;

void ComandoIf::debug_com_tab(int tab) {
    tab3(tab); cerr << "INI IF" << endl;
    
    tab3(tab + 1); cerr << "CONDICAO:" << endl;
    if (condicao != nullptr) condicao->debug_com_tab(tab + 2);
    
    tab3(tab + 1); cerr << "BLOCO VERDADEIRO:" << endl;
    for (Comando* cmd : blocoVerdadeiro) {
        if (cmd != nullptr) cmd->debug_com_tab(tab + 2);
    }
    
    if (!blocoFalso.empty()) {
        tab3(tab + 1); cerr << "BLOCO FALSO:" << endl;
        for (Comando* cmd : blocoFalso) {
            if (cmd != nullptr) cmd->debug_com_tab(tab + 2);
        }
    }
    
    tab3(tab); cerr << "FIM IF" << endl;
}

Stm* ComandoIf::gerar_IR() {
    return nullptr; 
}
