#include "Fator.hpp"
#include "Execucao.hpp"
#include "ExpressaoChamada.hpp"
#include <iostream>
#include <vector>
#include "../debug-util.hpp"

#include "../lab4-frame/FrameAcessoNoFrame.hpp"
#include "../lab4-frame/FrameAcessoTemp.hpp"

vector<Expressao*> extrai_argumentos(No_arv_parse* no_args) {
    vector<Expressao*> lista;
    
    if (no_args == nullptr || no_args->filhos.empty() || no_args->filhos[0]->simb == "")
        return lista;
    
    // Regra: args -> expOr argsTail
    lista.push_back(Expressao::extrai_expressao(no_args->filhos[0]));
    
    No_arv_parse* tail = no_args->filhos[1];
    
    while (tail != nullptr && !tail->filhos.empty() && tail->filhos[0]->simb != "") {
        lista.push_back(Expressao::extrai_expressao(tail->filhos[1]));
        tail = tail->filhos[2];
    }
    return lista;
}

Fator* Fator::extrai_Fator(No_arv_parse* no) {
    if (no == nullptr) return new Fator();

    //fator -> ID LPAREN args RPAREN
    if (no->filhos.size() == 4 && no->filhos[0]->simb == "ID" && no->filhos[1]->simb == "LPAREN") {
        ExpressaoChamada* chamada = new ExpressaoChamada();
        chamada->nome_funcao = new ID();
        chamada->nome_funcao->nome = no->filhos[0]->dado_extra; 
        chamada->argumentos = extrai_argumentos(no->filhos[2]);
        return chamada;
    }
    
    Fator* res = new Fator();

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
        return new Tipo(Tipo::INT);
    }
    else {
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
    return env.buscar(valor); 
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
    if (acesso_frame != nullptr) {
        if (auto no_frame = dynamic_cast<FrameAcessoNoFrame*>(acesso_frame)) {
            cerr << " -> [MEMORIA: pos FP" << (no_frame->posicao_no_frame > 0 ? "+" : "") << no_frame->posicao_no_frame << "]";
        } else if (auto temp = dynamic_cast<FrameAcessoTemp*>(acesso_frame)) {
            cerr << " -> [REGISTRADOR: id " << temp->id << "]";
        }
    }
    cerr << endl;
}