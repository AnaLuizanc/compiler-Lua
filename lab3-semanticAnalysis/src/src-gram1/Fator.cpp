#include "Fator.hpp"
#include "../regras.hpp"

Fator* Fator::extrai_Fator(No_arv_parse* no) {
    Fator* res = new Fator();

    switch(no->regra) {

        case REGRA_FATOR_ID:
            res->valor = no->filhos[0]->dado_extra;
            break;

        case REGRA_FATOR_NUMBER:
            res->valor = no->filhos[0]->dado_extra;
            break;

        case REGRA_FATOR_TRUE:
            res->valor = "true";
            break;

        case REGRA_FATOR_FALSE:
            res->valor = "false";
            break;

        case REGRA_FATOR_MINUS:
            res->valor = "-";
            res->interno = extrai_Fator(no->filhos[1]);
            break;

        case REGRA_FATOR_PAREN:
            // expOr está no filho[1]
            break;
    }

    return res;
}