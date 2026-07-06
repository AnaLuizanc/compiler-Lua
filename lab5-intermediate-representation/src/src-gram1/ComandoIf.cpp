#include "ComandoIf.hpp"
#include "../debug-util.hpp"
#include <iostream>
#include "../Tree/Stm.hpp"
#include "../Tree/StmSeq.hpp"
#include "../Tree/StmLabel.hpp"
#include "../Tree/StmJump.hpp"
#include "../Tree/StmCJump.hh"

using namespace std;

void ComandoIf::debug_com_tab(int tab) {
    tab3(tab); cerr << "INI IF" << endl;
    
    tab3(tab + 1); cerr << "CONDICAO:" << endl;
    if (condicao != nullptr) condicao->debug_com_tab(tab + 2);
    
    tab3(tab + 1); cerr << "BLOCO VERDADEIRO:" << endl;
    for (Comando* cmd : blocoVerdadeiro) {
        if (cmd != nullptr) cmd->debug_com_tab(tab + 2);
    }
    
    if (!blocoFalso.empty()) {
        tab3(tab + 1); cerr << "BLOCO FALSO:" << endl;
        for (Comando* cmd : blocoFalso) {
            if (cmd != nullptr) cmd->debug_com_tab(tab + 2);
        }
    }
    
    tab3(tab); cerr << "FIM IF" << endl;
}

Stm* ComandoIf::gerar_IR() {
    Exp* cond_ir = condicao->gerar_IR();
    
    string label_v = gerar_novo_label();
    string label_f = gerar_novo_label();
    string label_fim = gerar_novo_label();

    Stm* cjump = new StmCJump(cond_ir, label_v, label_f);
    Stm* bloco_v = sequenciar_lista_comandos(blocoVerdadeiro);
    Stm* bloco_f = sequenciar_lista_comandos(blocoFalso);

    Stm* seq = new StmSeq(cjump, new StmLabel(label_v));
    if (bloco_v) seq = new StmSeq(seq, bloco_v);
    
    seq = new StmSeq(seq, new StmJump(label_fim));
    seq = new StmSeq(seq, new StmLabel(label_f));
    
    if (bloco_f) seq = new StmSeq(seq, bloco_f);
    
    seq = new StmSeq(seq, new StmLabel(label_fim));

    return seq;
}
