#ifndef _COMANDO_ATRIBUICAO_HPP_
#define _COMANDO_ATRIBUICAO_HPP_
#include "Comando.hpp"
#include "ID.hpp"
#include "Expressao.hpp"

class ComandoAtribuicao : public Comando {
public:
    ID* esquerda;
    Expressao* direita;

    ComandoAtribuicao() {
        esquerda = NULL;
        direita = NULL;
    }
    void debug_com_tab(int tab) override;
    Stm* gerar_IR() override;
};
#endif