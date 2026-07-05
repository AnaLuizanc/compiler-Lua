#ifndef _EXPRESSAO_HPP_
#define _EXPRESSAO_HPP_

#include "../Arvore.hpp"
#include "TabelaSimbolos.hpp"
#include "Execucao.hpp"

class Exp;

class Expressao {
public:
    virtual Tipo* inferir_tipo(TabelaSimbolos& amb) = 0;
    static Expressao* extrai_expressao(No_arv_parse* no);
    virtual Valor* avaliar(Execucao& exec) = 0;
    virtual void debug_com_tab(int tab) = 0;
    virtual Exp* gerar_IR();
    virtual ~Expressao() {}
};

#endif