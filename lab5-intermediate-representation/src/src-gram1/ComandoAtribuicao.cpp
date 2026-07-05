#include "ComandoAtribuicao.hpp"
#include <iostream>
#include "../debug-util.hpp"
#include "../Tree/Stm.hpp"

#include "../Tree/StmMove.hpp"
#include "../Tree/ExpTemp.hpp"
#include "../Tree/ExpMem.hpp"
#include "../Tree/ExpBinop.hpp"
#include "../Tree/ExpConst.hpp"
#include "../Tree/ExpTempFramePointer.hpp"
#include "../Tree/OperadorSoma.hpp"
#include "../Frame/FrameAcessoNoFrame.hpp"
#include "../Frame/FrameAcessoTemp.hpp"

using namespace std;

void ComandoAtribuicao::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "INI ATRIB: " << esquerda->nome << " =" << endl;
    if (direita != NULL) {
        direita->debug_com_tab(tab + 1);
    }
    tab3(tab);
    cerr << "FIM ATRIB" << endl << endl;
}

Stm* ComandoAtribuicao::gerar_IR() {
    Exp* exp_origem = direita->gerar_IR(); 
    Exp* exp_destino = nullptr; 

    if (acesso != nullptr) {
        if (auto accTemp = dynamic_cast<FrameAcessoTemp*>(acesso)) {
            exp_destino = new ExpTemp(accTemp->id);
        } 
        else if (auto accMem = dynamic_cast<FrameAcessoNoFrame*>(acesso)) {
            Exp* fp = new ExpTempFramePointer();
            Exp* offset = new ExpConst(accMem->posicao_no_frame);
            exp_destino = new ExpMem(new ExpBinop(new OperadorSoma(), fp, offset));
        }
    }
    if (exp_destino != nullptr && exp_origem != nullptr) {
        return new StmMove(exp_destino, exp_origem);
    }
    
    return nullptr;
}
