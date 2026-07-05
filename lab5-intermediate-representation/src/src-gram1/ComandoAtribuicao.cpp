#include "ComandoAtribuicao.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Stm.hpp"
using namespace std;

void ComandoAtribuicao::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "INI ATRIB: " << esquerda->nome << " =" << endl;
    if (direita != NULL) {
        direita->debug_com_tab(tab + 1);
    }
    tab3(tab);
    cerr << "FIM ATRIB" << endl << endl;
}

Stm* ComandoAtribuicao::gerar_IR() {
    return nullptr;
}
