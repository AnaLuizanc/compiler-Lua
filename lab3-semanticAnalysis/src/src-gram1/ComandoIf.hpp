#ifndef _COMANDO_IF_HPP_
#define _COMANDO_IF_HPP_

#include "Comando.hpp"
#include "Expressao.hpp"
#include "../debug-util.hpp"
#include <iostream>
#include <vector>

using namespace std;

class ComandoIf : public Comando {
public:
    Expressao* condicao;
    vector<Comando*> blocoVerdadeiro;
    vector<Comando*> blocoFalso; // Pode ficar vazio se nao houver ELSE

    void debug_com_tab(int tab) override {
        tab3(tab); cerr << "Comando IF" << endl;
    }
};

#endif