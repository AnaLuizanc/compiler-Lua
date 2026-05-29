#ifndef _TABELA_SIMBOLOS_HPP_
#define _TABELA_SIMBOLOS_HPP_

#include <string>
#include <vector>
#include <map>
#include "Tipo.hpp"

using namespace std;

class TabelaSimbolos {
private:
    // Uma pilha de escopos. Cada escopo mapeia um nome (string) para o seu Tipo.
    vector<map<string, Tipo*>> pilha_escopos;

public:
    TabelaSimbolos();
    
    // Gestão de Escopos
    void entrar_escopo();
    void sair_escopo();
    
    // Operações Semânticas
    // Retorna false se a variável já existir no escopo atual
    bool declarar_variavel(string nome, Tipo* tipo);
    
    // Procura a variável do escopo mais interno para o mais externo. Retorna NULL se não existir.
    Tipo* buscar_variavel(string nome);
};

#endif