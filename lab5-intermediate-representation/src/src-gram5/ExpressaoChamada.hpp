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

    Tipo* inferir_tipo(TabelaSimbolos& /*amb*/) override { 
        return new Tipo(Tipo::INT); 
    }

    Valor* avaliar(Execucao& /*exec*/) override { 
        return new Valor(0); 
    }

    void debug_com_tab(int tab) override {
        tab3(tab);
        cerr << "CHAMADA DE FUNCAO [" << (nome_funcao ? nome_funcao->nome : "NULL") << "] (" << endl;
        for (auto arg : argumentos) {
            if(arg) arg->debug_com_tab(tab + 1);
        }
        tab3(tab);
        cerr << ")" << endl;
    }
};

#endif