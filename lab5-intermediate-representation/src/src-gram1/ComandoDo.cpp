#include "ComandoDo.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Stm.hpp"

using namespace std;

void ComandoDo::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "INI DO" << endl;
    
    for (Comando* cmd : bloco) {
        if (cmd != nullptr) {
            cmd->debug_com_tab(tab + 1);
        }
    }
    
    tab3(tab);
    cerr << "FIM DO" << endl;
}

Stm* ComandoDo::gerar_IR() {
    return nullptr;
}