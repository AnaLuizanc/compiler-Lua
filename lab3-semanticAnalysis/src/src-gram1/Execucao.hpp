#ifndef _EXECUCAO_HPP_
#define _EXECUCAO_HPP_

#include <map>
#include <vector>
#include <string>
#include "Valor.hpp"

class Execucao {
    std::vector<std::map<std::string, Valor*>> pilha;
public:
    Execucao() { pilha.push_back(std::map<std::string, Valor*>()); }
    
    void entrar() { pilha.push_back(std::map<std::string, Valor*>()); }
    void sair() { pilha.pop_back(); }
    
    void definir(std::string nome, Valor* v) { pilha.back()[nome] = v; }
    
    Valor* buscar(std::string nome) {
        for (auto it = pilha.rbegin(); it != pilha.rend(); ++it) {
            if (it->count(nome)) return (*it)[nome];
        }
        return nullptr;
    }
};

#endif