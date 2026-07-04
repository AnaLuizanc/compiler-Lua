#ifndef _TIPO_HPP_
#define _TIPO_HPP_
#include "../Arvore.hpp"
#include <string>
using namespace std;

class Tipo {
public:
    enum Valor {
        INT,
        FLOAT,
        BOOL
    };

    Valor valor;

    Tipo(Valor valor);
    string nome() const;
    static Tipo* extrai_Tipo(No_arv_parse* no);
};

#endif
