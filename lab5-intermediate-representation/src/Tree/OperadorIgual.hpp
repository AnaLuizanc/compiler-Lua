#ifndef _OPERADOR_IGUAL_HPP_
#define _OPERADOR_IGUAL_HPP_
#include <string>
#include "Operador.hpp"
using namespace std;

class OperadorIgual : public Operador {
public:
    string to_string() override { return "=="; }
};
#endif