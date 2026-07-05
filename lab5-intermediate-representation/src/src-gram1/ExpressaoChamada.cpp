#include "ExpressaoChamada.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Exp.hpp"


Tipo* ExpressaoChamada::inferir_tipo(TabelaSimbolos& /*amb*/){ 
    return new Tipo(Tipo::INT); 
}

Valor* ExpressaoChamada::avaliar(Execucao& /*exec*/){ 
    return new Valor(0); 
}

void ExpressaoChamada::debug_com_tab(int tab){
    tab3(tab);
    cerr << "CHAMADA DE FUNCAO [" << (nome_funcao ? nome_funcao->nome : "NULL") << "] (" << endl;
    for (auto arg : argumentos) {
        if(arg) arg->debug_com_tab(tab + 1);
    }
    tab3(tab);
    cerr << ")" << endl;
}

Exp* ExpressaoChamada::gerar_IR() {
    return nullptr;
}
