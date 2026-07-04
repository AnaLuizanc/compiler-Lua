#ifndef _EXPRESSAO_BINARIA_HPP_
#define _EXPRESSAO_BINARIA_HPP_

#include <string>
#include "Expressao.hpp"

using namespace std;

class ExpressaoBinaria : public Expressao {
public:
    string nome_op;
    string simbolo;

    Expressao* esquerda;
    Expressao* direita;

    ExpressaoBinaria(string nome, string sim) : nome_op(nome), simbolo(sim), esquerda(nullptr), direita(nullptr) {}

    Tipo* inferir_tipo(TabelaSimbolos& amb) override;

    Valor* avaliar(Execucao& exec) override;

    void debug_com_tab(int tab) override;
};

#endif