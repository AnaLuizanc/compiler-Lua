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
Valor* ExpressaoBinaria::avaliar(Execucao& exec) {
    Valor* esq = esquerda->avaliar(exec);
    Valor* dir = direita->avaliar(exec);

    // Identifica se há coerção para FLOAT
    bool isFloat = (esq->tipo == Tipo::FLOAT || dir->tipo == Tipo::FLOAT);
    float f_esq = (esq->tipo == Tipo::INT) ? esq->dados.i : esq->dados.f;
    float f_dir = (dir->tipo == Tipo::INT) ? dir->dados.i : dir->dados.f;

    // Aritmética
    if (simbolo == "+") {
        if (isFloat) return new Valor(f_esq + f_dir);
        return new Valor(esq->dados.i + dir->dados.i);
    }
    if (simbolo == "-") {
        if (isFloat) return new Valor(f_esq - f_dir);
        return new Valor(esq->dados.i - dir->dados.i);
    }
    if (simbolo == "*") {
        if (isFloat) return new Valor(f_esq * f_dir);
        return new Valor(esq->dados.i * dir->dados.i);
    }
    if (simbolo == "/") {
        if (isFloat) return new Valor(f_esq / f_dir);
        return new Valor(esq->dados.i / dir->dados.i);
    }
    if (simbolo == "%") {
        return new Valor(esq->dados.i % dir->dados.i); // Módulo é exclusivo de INT
    }

    // Relacionais
    if (simbolo == "==") {
        if (isFloat) return new Valor(f_esq == f_dir);
        if (esq->tipo == Tipo::BOOL) return new Valor(esq->dados.b == dir->dados.b);
        return new Valor(esq->dados.i == dir->dados.i);
    }
    if (simbolo == "~=") {
        if (isFloat) return new Valor(f_esq != f_dir);
        if (esq->tipo == Tipo::BOOL) return new Valor(esq->dados.b != dir->dados.b);
        return new Valor(esq->dados.i != dir->dados.i);
    }
    if (simbolo == "<") {
        if (isFloat) return new Valor(f_esq < f_dir);
        return new Valor(esq->dados.i < dir->dados.i);
    }
    if (simbolo == "<=") {
        if (isFloat) return new Valor(f_esq <= f_dir);
        return new Valor(esq->dados.i <= dir->dados.i);
    }
    if (simbolo == ">") {
        if (isFloat) return new Valor(f_esq > f_dir);
        return new Valor(esq->dados.i > dir->dados.i);
    }
    if (simbolo == ">=") {
        if (isFloat) return new Valor(f_esq >= f_dir);
        return new Valor(esq->dados.i >= dir->dados.i);
    }

    // Lógicos
    if (simbolo == "and") return new Valor(esq->dados.b && dir->dados.b);
    if (simbolo == "or") return new Valor(esq->dados.b || dir->dados.b);

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