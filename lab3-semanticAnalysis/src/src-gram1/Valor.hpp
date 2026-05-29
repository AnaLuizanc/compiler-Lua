#ifndef _VALOR_HPP_
#define _VALOR_HPP_

#include <string>
#include <iostream>
#include <iomanip>
#include "Tipo.hpp"

class Valor {
public:
    Tipo::Valor tipo;
    union {
        int i;
        float f;
        bool b;
    } dados;

    Valor(int i) : tipo(Tipo::INT) { dados.i = i; }
    Valor(float f) : tipo(Tipo::FLOAT) { dados.f = f; }
    Valor(bool b) : tipo(Tipo::BOOL) { dados.b = b; }

    void imprimir() {
        if (tipo == Tipo::INT) std::cout << dados.i << std::endl;
        else if (tipo == Tipo::FLOAT) std::cout << std::fixed << std::setprecision(2) << dados.f << std::endl;
        else if (tipo == Tipo::BOOL) std::cout << (dados.b ? "true" : "false") << std::endl;
    }
};

#endif