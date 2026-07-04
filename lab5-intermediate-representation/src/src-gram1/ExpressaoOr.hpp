#ifndef _EXPRESSAO_OR_HPP_
#define _EXPRESSAO_OR_HPP_

#include "Expressao.hpp"

class ExpressaoOr : public Expressao {
public:
    Expressao* raiz;

    static ExpressaoOr* extrai_ExpressaoOr(No_arv_parse* no);
};

#endif