#ifndef _OPERADOR_MENOR_HPP_
#define _OPERADOR_MENOR_HPP_
#include <string>
#include "Operador.hpp"
using namespace std;

class OperadorMenor : public Operador {
public:
    string to_string() override { return "<"; }
};
#endif