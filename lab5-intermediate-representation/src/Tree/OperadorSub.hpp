#ifndef _OPERADOR_SUB_HPP_
#define _OPERADOR_SUB_HPP_
#include "Operador.hpp"

class OperadorSub : public Operador {
public:
    OperadorSub() {}
    string to_string() override { return "-"; }
};

#endif
