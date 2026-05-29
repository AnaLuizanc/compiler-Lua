#include "ExpressaoBinaria.hpp"
#include <iostream>
#include "../debug-util.hpp"

Tipo* ExpressaoBinaria::inferir_tipo(TabelaSimbolos& amb) {
    Tipo* esq = esquerda->inferir_tipo(amb);
    Tipo* dir = direita->inferir_tipo(amb);

    if (esq == nullptr || dir == nullptr) return nullptr; // Erro já apanhado nos filhos

    // Operadores Aritméticos
    if (simbolo == "+" || simbolo == "-" || simbolo == "*" || simbolo == "/" || simbolo == "%") {
        if ((esq->valor != Tipo::INT && esq->valor != Tipo::FLOAT) || (dir->valor != Tipo::INT && dir->valor != Tipo::FLOAT)) {
            cerr << "Erro Semantico: Operador '" << simbolo << "' exige operandos numericos." << endl;
            exit(1);
        }
        
        // se float + int retorrna float
        if (esq->valor == Tipo::FLOAT || dir->valor == Tipo::FLOAT) {
            return new Tipo(Tipo::FLOAT);
        }
        return new Tipo(Tipo::INT); 
    }

    // Operadores Relacionais
    if (simbolo == "==" || simbolo == "~=" || simbolo == "<" || simbolo == "<=" || simbolo == ">" || simbolo == ">=") {
        if (esq->valor != dir->valor) {
            cerr << "Erro Semantico: Comparacao '" << simbolo << "' entre tipos incompativeis (" 
                 << esq->nome() << " e " << dir->nome() << ")." << endl;
            exit(1);
        }
        return new Tipo(Tipo::BOOL); // Comparações retornam sempre booleanos
    }

    // Operadores Lógicos
    if (simbolo == "and" || simbolo == "or") {
        if (esq->valor != Tipo::BOOL || dir->valor != Tipo::BOOL) {
            cerr << "Erro Semantico: Operador logico '" << simbolo << "' exige operandos booleanos." << endl;
            exit(1);
        }
        return new Tipo(Tipo::BOOL); // Operações lógicas retornam Booleanos
    }

    return nullptr;
}

void ExpressaoBinaria::debug_com_tab(int tab) {
    tab3(tab);
    cerr << simbolo << " [ INI " << nome_op << endl;
    
    if (esquerda != nullptr) esquerda->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << endl;
    
    if (direita != nullptr) direita->debug_com_tab(tab + 1);
    
    tab3(tab);
    cerr << simbolo << " ] FIM " << nome_op << endl;
}