#ifndef _VALOR_HPP_
#define _VALOR_HPP_

#include <string>
#include <iostream>
#include <iomanip>
#include "Tipo.hpp"

using namespace std;

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
        if (tipo == Tipo::INT) cout << dados.i << endl;
        else if (tipo == Tipo::FLOAT) cout << fixed << setprecision(2) << dados.f << endl;
        else if (tipo == Tipo::BOOL) cout << (dados.b ? "true" : "false") << endl;
    }
};

#endif