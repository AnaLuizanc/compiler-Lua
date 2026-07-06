#ifndef _OPERADOR_SOMA_HPP_
#define _OPERADOR_SOMA_HPP_
#include "Operador.hpp"

class OperadorSoma : public Operador {
public:
    OperadorSoma() {}
    string to_string() override { return "+"; }
};

#endif
