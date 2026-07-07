#ifndef _OPERADOR_MAIOR_IGUAL_HPP_
#define _OPERADOR_MAIOR_IGUAL_HPP_

#include <string>
#include "Operador.hpp"
using namespace std;

class OperadorMaiorIgual : public Operador {
public:
    string to_string() override { return ">="; }
};

#endif
