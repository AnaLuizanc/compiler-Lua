#ifndef _ANALISADOR_SEMANTICO_HPP_
#define _ANALISADOR_SEMANTICO_HPP_

#include "Funcao.hpp"
#include "TabelaSimbolos.hpp"
#include "Comando.hpp"
#include "Execucao.hpp"
#include "Valor.hpp"

class AnalisadorSemantico {
private:
    TabelaSimbolos amb;
    Tipo* retorno_esperado;

    void validar_comandos(const std::vector<Comando*>& comandos, Execucao& exec);

public:
    Valor* ultimo_valor = nullptr; 

    void analisar(Funcao* func);
};

#endif