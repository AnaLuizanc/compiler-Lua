#ifndef _FATOR_HPP_
#define _FATOR_HPP_

#include <string>
#include "Expressao.hpp"
#include "ID.hpp"
#include "../Frame/FrameAcesso.hpp" 

using namespace std;

class Fator : public Expressao {
public:
    string valor;
    
    Expressao* interno = nullptr; 

    FrameAcesso* acesso_frame = nullptr; 

    static Fator* extrai_Fator(No_arv_parse* no);
    
    Tipo* inferir_tipo(TabelaSimbolos& amb) override;

    Valor* avaliar(Execucao& env);

    void debug_com_tab(int tab) override; 

    Exp* gerar_IR() override;
};

#endif