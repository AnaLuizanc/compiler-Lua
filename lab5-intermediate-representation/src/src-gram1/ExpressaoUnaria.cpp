#include "ExpressaoUnaria.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Exp.hpp"

Tipo* ExpressaoUnaria::inferir_tipo(TabelaSimbolos& amb) {
    Tipo* t = expressao->inferir_tipo(amb);
    if (t == nullptr) return nullptr;

    if (simbolo == "not") {
        if (t->valor != Tipo::BOOL) {
            cerr << "Erro Semantico: Operador 'not' aplicado a tipo nao booleano." << endl;
            exit(1);
        }
        return new Tipo(Tipo::BOOL);
    }
    return t;
}

Valor* ExpressaoUnaria::avaliar(Execucao& exec) {
    Valor* val = expressao->avaliar(exec);
    
    if (val == nullptr) {
        cerr << "Erro de Execucao: Operando nulo (variavel nao inicializada)." << endl;
        exit(1);
    }

    if (simbolo == "not") {
        return new Valor(!val->dados.b);
    }
    
    return val;
}

void ExpressaoUnaria::debug_com_tab(int tab) {
    tab3(tab);
    cerr << simbolo << " [ INI " << nome_op << endl;
    
    if (expressao != nullptr) expressao->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << " ] FIM " << nome_op << endl;
}

Exp* ExpressaoUnaria::gerar_IR() {
    return nullptr; 
}
