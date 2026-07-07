#ifndef _OPERADOR_MENOR_IGUAL_HPP_
#define _OPERADOR_MENOR_IGUAL_HPP_
#include <string>
#include "Operador.hpp"
using namespace std;

class OperadorMenorIgual : public Operador {
public:
    string to_string() override { return "<="; }
};
#endif