#ifndef _OPERADOR_MULT_HPP_
#define _OPERADOR_MULT_HPP_
#include "Operador.hpp"

class OperadorMult : public Operador {
public:
    OperadorMult() {}
    string to_string() override { return "*"; }
};

#endif