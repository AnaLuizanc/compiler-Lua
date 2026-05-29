#include "Expressao.hpp"
#include "Fator.hpp"

using namespace std;

Expressao* Expressao::extrai_expressao(No_arv_parse* no) {

    if (no == nullptr)
        return nullptr;

    switch(no->regra) {

        /*
         17 -> fator -> ID
         18 -> fator -> FALSE
         19 -> fator -> TRUE
         20 -> fator -> NUMBER
         21 -> fator -> MINUS fator
         22 -> fator -> LPAREN expOr RPAREN
        */

        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
            return Fator::extrai_Fator(no);

        /*
         termo -> fator termoLinha
         exp -> termo expLinha
         expRel -> exp expRelLinha
         expNot -> expRel
         expAnd -> expNot expAndLinha
         expOr -> expAnd expOrLinha
        */

        default:
            if (no->filhos.size() > 0) {
                return extrai_expressao(no->filhos[0]);
            }

            return nullptr;
    }
}

void Expressao::debug_com_tab(int tab) {
}