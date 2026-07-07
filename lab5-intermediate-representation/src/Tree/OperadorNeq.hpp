#ifndef _OPERADOR_NEQ_HPP_
#define _OPERADOR_NEQ_HPP_

#include <string>
#include "Operador.hpp"
using namespace std;

class OperadorNeq : public Operador {
public:
    string to_string() override { return "~="; }
};

#endif
