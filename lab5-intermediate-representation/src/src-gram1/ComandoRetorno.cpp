#include "ComandoRetorno.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Stm.hpp"
using namespace std;

void ComandoRetorno::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "INI RETURN" << endl;
    if (expressao != NULL) {
        expressao->debug_com_tab(tab + 1);
    }
    tab3(tab);
    cerr << "FIM RETURN" << endl;
}

Stm* ComandoRetorno::gerar_IR() {
    return nullptr;
}
