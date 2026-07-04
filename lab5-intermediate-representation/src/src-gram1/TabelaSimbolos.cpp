#include "TabelaSimbolos.hpp"
#include <iostream>

using namespace std;

TabelaSimbolos::TabelaSimbolos() {
    entrar_escopo();
}

void TabelaSimbolos::entrar_escopo() {
    pilha_escopos.push_back(map<string, Tipo*>());
}

void TabelaSimbolos::sair_escopo() {
    if (!pilha_escopos.empty())
        pilha_escopos.pop_back();
}

bool TabelaSimbolos::declarar_variavel(string nome, Tipo* tipo) {
    if (pilha_escopos.empty()) return false;

    map<string, Tipo*>& escopo_atual = pilha_escopos.back();

    if (escopo_atual.find(nome) != escopo_atual.end())
        return false; 

    escopo_atual[nome] = tipo;
    return true;
}

Tipo* TabelaSimbolos::buscar_variavel(string nome) {
    for (auto it = pilha_escopos.rbegin(); it != pilha_escopos.rend(); ++it) {
        map<string, Tipo*>& escopo = *it;
        if (escopo.find(nome) != escopo.end())
            return escopo[nome];
    }
    return nullptr; 
}