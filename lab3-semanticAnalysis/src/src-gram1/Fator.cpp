#include "Fator.hpp"
#include "Execucao.hpp"
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

Tipo* Fator::inferir_tipo(TabelaSimbolos& amb) {
    if (valor == "PAREN") {
        return interno->inferir_tipo(amb);
    }
    else if (valor == "-") {
        Tipo* t = interno->inferir_tipo(amb);
        if (t != nullptr && t->valor != Tipo::INT && t->valor != Tipo::FLOAT) {
            cerr << "Erro Semantico: Operador '-' unario aplicado a tipo nao numerico." << endl;
            exit(1);
        }
        return t;
    }
    else if (valor == "true" || valor == "false") {
        return new Tipo(Tipo::BOOL);
    }
    else if (valor.length() > 0 && isdigit(valor[0])) {
        // Se começa por um dígito, é um número (assumiremos INT para simplificar)
        return new Tipo(Tipo::INT);
    }
    else {
        // Se não é nenhum dos anteriores, é o ID de uma variável
        Tipo* t = amb.buscar_variavel(valor);
        if (t == nullptr) {
            cerr << "Erro Semantico: Variavel '" << valor << "' nao foi declarada neste escopo." << endl;
            exit(1);
        }
        return t;
    }
}

Valor* Fator::avaliar(Execucao& env) {
    if (valor == "PAREN") return interno->avaliar(env);
    if (isdigit(valor[0])) return new Valor(stoi(valor));
    if (valor == "true") return new Valor(true);
    if (valor == "false") return new Valor(false);
    return env.buscar(valor); // Busca o valor da variável na memória
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