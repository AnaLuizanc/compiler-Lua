#ifndef _FATOR_HPP_
#define _FATOR_HPP_

#include <string>
#include "Expressao.hpp"
#include "ID.hpp"

using namespace std;

class Fator : public Expressao {
public:
    string valor;
    
    Expressao* interno = nullptr; 

    static Fator* extrai_Fator(No_arv_parse* no);
    
    Tipo* inferir_tipo(TabelaSimbolos& amb) override;

    Valor* Fator::avaliar(Execucao& env);

    void debug_com_tab(int tab) override; 
};

#endif