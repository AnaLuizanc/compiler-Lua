#ifndef _EXPRESSAO_CHAMADA_HPP_
#define _EXPRESSAO_CHAMADA_HPP_

#include <string>
#include <vector>
#include "Fator.hpp"
#include "ID.hpp"
#include "Valor.hpp"
#include "Tipo.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

class ExpressaoChamada : public Fator {
public:
    ID* nome_funcao;
    vector<Expressao*> argumentos;

    ExpressaoChamada() {
        nome_funcao = nullptr;
        this->valor = "CHAMADA"; 
    }

    Tipo* inferir_tipo(TabelaSimbolos& /*amb*/) override;

    Valor* avaliar(Execucao& /*exec*/) override;

    void debug_com_tab(int tab) override;

    Exp* gerar_IR() override;
};

#endif