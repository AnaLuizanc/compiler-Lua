#ifndef _EXECUCAO_HPP_
#define _EXECUCAO_HPP_

#include <map>
#include <vector>
#include <string>
#include "Valor.hpp"

using namespace std;
    
class Execucao {
    vector<map<string, Valor*>> pilha;
public:
    Execucao() { pilha.push_back(map<string, Valor*>()); }
    
    void entrar() { pilha.push_back(map<string, Valor*>()); }
    void sair() { pilha.pop_back(); }
    
    void definir(string nome, Valor* v) { pilha.back()[nome] = v; }
    
    Valor* buscar(string nome) {
        for (auto it = pilha.rbegin(); it != pilha.rend(); ++it) {
            if (it->count(nome)) return (*it)[nome];
        }
        return nullptr;
    }
};

#endif