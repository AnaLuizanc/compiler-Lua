#ifndef _TABELA_SIMBOLOS_HPP_
#define _TABELA_SIMBOLOS_HPP_

#include <string>
#include <vector>
#include <map>
#include "Tipo.hpp"

using namespace std;

class TabelaSimbolos {
private:
    vector<map<string, Tipo*>> pilha_escopos;

public:
    TabelaSimbolos();
    
    void entrar_escopo();
    void sair_escopo();
    bool declarar_variavel(string nome, Tipo* tipo);
    Tipo* buscar_variavel(string nome);
};

#endif