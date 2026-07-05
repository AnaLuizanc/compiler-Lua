#ifndef _EXPRESSAO_UNARIA_HPP_
#define _EXPRESSAO_UNARIA_HPP_

#include <string>
#include "Expressao.hpp"

using namespace std;

class ExpressaoUnaria : public Expressao {
public:
    string nome_op;
    string simbolo;
    Expressao* expressao;

    ExpressaoUnaria(string nome, string sim) : nome_op(nome), simbolo(sim), expressao(nullptr) {}

    Tipo* inferir_tipo(TabelaSimbolos& amb) override;

    Valor* avaliar(Execucao& exec) override;

    void debug_com_tab(int tab) override;

    Exp* gerar_IR() override;
};

#endif