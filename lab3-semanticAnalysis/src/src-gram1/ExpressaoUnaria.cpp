#include "ExpressaoUnaria.hpp"
#include <iostream>
#include "../debug-util.hpp"

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

void ExpressaoUnaria::debug_com_tab(int tab) {
    tab3(tab);
    cerr << simbolo << " [ INI " << nome_op << endl;
    
    if (expressao != nullptr) expressao->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << " ] FIM " << nome_op << endl;
}