#include "Fator.hpp"
#include <iostream>
#include "../debug-util.hpp"

Fator* Fator::extrai_Fator(No_arv_parse* no) {
    Fator* res = new Fator();
    if (no == nullptr) return res;

    // fator -> ID | NUMBER | TRUE | FALSE
    if (no->filhos.size() == 1) {
        string s = no->filhos[0]->simb;
        if (s == "ID" || s == "NUMBER") {
            res->valor = no->filhos[0]->dado_extra;
        } else if (s == "TRUE") {
            res->valor = "true";
        } else if (s == "FALSE") {
            res->valor = "false";
        }
    }
    // fator -> MINUS fator
    else if (no->filhos.size() == 2 && no->filhos[0]->simb == "MINUS") {
        res->valor = "-";
        res->interno = extrai_Fator(no->filhos[1]);
    }
    // fator -> LPAREN expOr RPAREN
    else if (no->filhos.size() == 3 && no->filhos[0]->simb == "LPAREN") {
        res->valor = "PAREN";
        res->interno = Expressao::extrai_expressao(no->filhos[1]);
    }

    return res;
}

void Fator::debug_com_tab(int tab) {
    tab3(tab);
    
    if (valor == "PAREN") {
        cerr << "( " << endl;
        if (interno != nullptr) interno->debug_com_tab(tab + 1);
        tab3(tab);
        cerr << ")" << endl;
    }
    else if (valor == "-") {
        cerr << "-";
        if (interno != nullptr) interno->debug_com_tab(0);
    }
    else if (valor == "true" || valor == "false") {
        cerr << valor << " [BOOL]" << endl;
    }
    else if (valor.length() > 0 && isdigit(valor[0])) {
        cerr << valor << " [INT]" << endl;
    }
    else {
        cerr << "VAR[" << valor << "]" << endl;
    }
}