#include "ComandoWhile.hpp"
#include "../debug-util.hpp"
#include "../Tree/Stm.hpp"
#include "../Tree/StmSeq.hpp"
#include "../Tree/StmLabel.hpp"
#include "../Tree/StmJump.hpp"
#include "../Tree/StmCJump.hh"
#include <iostream>

using namespace std;

void ComandoWhile::debug_com_tab(int tab) {
    tab3(tab); cerr << "INI WHILE" << endl;
    
    tab3(tab + 1); cerr << "CONDICAO:" << endl;
    if (condicao != nullptr) condicao->debug_com_tab(tab + 2);
    
    tab3(tab + 1); cerr << "BLOCO:" << endl;
    for (Comando* cmd : bloco) {
        if (cmd != nullptr) cmd->debug_com_tab(tab + 2);
    }
    
    tab3(tab); cerr << "FIM WHILE" << endl;
}

Stm* ComandoWhile::gerar_IR() {
    Exp* cond_ir = condicao->gerar_IR();
    
    string label_teste = gerar_novo_label();
    string label_inicio = gerar_novo_label();
    string label_fim = gerar_novo_label();

    Stm* seq = new StmLabel(label_teste);
    seq = new StmSeq(seq, new StmCJump(cond_ir, label_inicio, label_fim));
    seq = new StmSeq(seq, new StmLabel(label_inicio));

    Stm* bloco_ir = sequenciar_lista_comandos(bloco);
    if (bloco_ir) seq = new StmSeq(seq, bloco_ir);

    seq = new StmSeq(seq, new StmJump(label_teste));
    seq = new StmSeq(seq, new StmLabel(label_fim));

    return seq;
}
