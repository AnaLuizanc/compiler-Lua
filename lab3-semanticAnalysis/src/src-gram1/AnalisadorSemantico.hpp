#ifndef _ANALISADOR_SEMANTICO_HPP_
#define _ANALISADOR_SEMANTICO_HPP_

#include "Funcao.hpp"
#include "TabelaSimbolos.hpp"
#include "Comando.hpp"

class AnalisadorSemantico {
private:
    TabelaSimbolos amb;
    Tipo* retorno_esperado;

    // Método recursivo para percorrer blocos de comandos
    void validar_comandos(const std::vector<Comando*>& comandos);

public:
    // Ponto de entrada da análise
    void analisar(Funcao* func);
};

#endif