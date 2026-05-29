#include "TabelaSimbolos.hpp"
#include <iostream>

using namespace std;

TabelaSimbolos::TabelaSimbolos() {
    // Ao instanciar a tabela, criamos logo um escopo global base
    entrar_escopo();
}

void TabelaSimbolos::entrar_escopo() {
    // Empilha um novo dicionário vazio
    pilha_escopos.push_back(map<string, Tipo*>());
}

void TabelaSimbolos::sair_escopo() {
    // Desempilha o dicionário do topo, destruindo as variáveis daquele bloco
    if (!pilha_escopos.empty()) {
        pilha_escopos.pop_back();
    }
}

bool TabelaSimbolos::declarar_variavel(string nome, Tipo* tipo) {
    if (pilha_escopos.empty()) return false;

    // Referência para o escopo que está no topo da pilha
    map<string, Tipo*>& escopo_atual = pilha_escopos.back();

    // Regra Semântica: Uma variável não pode ser declarada duas vezes no MESMO escopo
    if (escopo_atual.find(nome) != escopo_atual.end()) {
        return false; 
    }

    escopo_atual[nome] = tipo;
    return true;
}

Tipo* TabelaSimbolos::buscar_variavel(string nome) {
    // Procura de cima para baixo (do rbegin até ao rend)
    // Isso garante que a variável mais interna é encontrada primeiro (Shadowing)
    for (auto it = pilha_escopos.rbegin(); it != pilha_escopos.rend(); ++it) {
        map<string, Tipo*>& escopo = *it;
        
        if (escopo.find(nome) != escopo.end()) {
            return escopo[nome];
        }
    }
    
    // Se percorreu toda a pilha e não encontrou, a variável não foi declarada
    return nullptr; 
}