#ifndef _COMANDO_WHILE_HPP_
#define _COMANDO_WHILE_HPP_

#include "Comando.hpp"
#include "Expressao.hpp"
#include "../debug-util.hpp"
#include <iostream>
#include <vector>

using namespace std;

class ComandoWhile : public Comando {
public:
    Expressao* condicao;
    vector<Comando*> bloco;

    void debug_com_tab(int tab) override;
};

#endif