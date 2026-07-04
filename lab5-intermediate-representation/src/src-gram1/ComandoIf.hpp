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
    vector<Comando*> blocoFalso;

    void debug_com_tab(int tab) override;
};

#endif