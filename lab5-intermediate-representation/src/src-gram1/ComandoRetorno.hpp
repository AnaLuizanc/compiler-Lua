#ifndef _COMANDO_RETORNO_HPP_
#define _COMANDO_RETORNO_HPP_
#include "Comando.hpp"
#include "Expressao.hpp"

class ComandoRetorno : public Comando {
public:
    Expressao* expressao;

    ComandoRetorno() { expressao = NULL; }
    void debug_com_tab(int tab) override;

    Stm* gerar_IR() override;
};
#endif