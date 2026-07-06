#include "ComandoRetorno.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Stm.hpp"
#include "../Tree/StmReturn.hpp"
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
    Exp* exp_ir = nullptr;
        
    if (expressao != nullptr)
        exp_ir = expressao->gerar_IR();
    
    return new StmReturn(exp_ir);
}
