#ifndef _EXP_BINARIA_HPP_
#define _EXP_BINARIA_HPP_

#include <string>
#include "Expressao.hpp"

using namespace std;

class ExpBinaria : public Expressao {
public:
    string operador;

    Expressao* esquerda;
    Expressao* direita;
};

#endif