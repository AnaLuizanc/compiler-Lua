#ifndef _OPERADOR_MAIOR_HPP_
#define _OPERADOR_MAIOR_HPP_

#include <string>
#include "Operador.hpp"
using namespace std;

class OperadorMaior : public Operador {
public:
    string to_string() override { return ">"; }
};

#endif
