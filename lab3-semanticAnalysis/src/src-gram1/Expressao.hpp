#ifndef _EXPRESSAO_HPP_
#define _EXPRESSAO_HPP_

#include "../Arvore.hpp"
#include "TabelaSimbolos.hpp"

class Expressao {
public:
    virtual void debug_com_tab(int tab) = 0;
    
    virtual Tipo* inferir_tipo(TabelaSimbolos& amb) = 0; 
    
    static Expressao* extrai_expressao(No_arv_parse* no);

    Valor* Fator::avaliar(Execucao& env);
};

#endif