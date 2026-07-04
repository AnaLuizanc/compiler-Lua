#include "Expressao.hpp"
#include "Fator.hpp"
#include "ExpressaoBinaria.hpp"
#include "ExpressaoUnaria.hpp"

using namespace std;

Expressao* extrai_expOr(No_arv_parse* no);
Expressao* extrai_expOrLinha(No_arv_parse* no, Expressao* esq);
Expressao* extrai_expAnd(No_arv_parse* no);
Expressao* extrai_expAndLinha(No_arv_parse* no, Expressao* esq);
Expressao* extrai_expNot(No_arv_parse* no);
Expressao* extrai_expRel(No_arv_parse* no);
Expressao* extrai_expRelLinha(No_arv_parse* no, Expressao* esq);
Expressao* extrai_exp_nivel(No_arv_parse* no);
Expressao* extrai_expLinha(No_arv_parse* no, Expressao* esq);
Expressao* extrai_termo_nivel(No_arv_parse* no);
Expressao* extrai_termoLinha(No_arv_parse* no, Expressao* esq);

Expressao* Expressao::extrai_expressao(No_arv_parse* no) {
    if (no == nullptr) return nullptr;

    if (no->simb == "expOr") return extrai_expOr(no);

    if (no->filhos.size() > 0) return extrai_expressao(no->filhos[0]);
    return nullptr;
}

// ---- LÓGICA OR
Expressao* extrai_expOr(No_arv_parse* no) {
    Expressao* esq = extrai_expAnd(no->filhos[0]);
    return extrai_expOrLinha(no->filhos[1], esq);
}
Expressao* extrai_expOrLinha(No_arv_parse* no, Expressao* esq) {
    if (no->filhos.size() == 0) return esq;
    Expressao* dir = extrai_expAnd(no->filhos[1]);
    ExpressaoBinaria* bin = new ExpressaoBinaria("Or", "or");
    bin->esquerda = esq; bin->direita = dir;
    return extrai_expOrLinha(no->filhos[2], bin);
}

// ---- LÓGICA AND
Expressao* extrai_expAnd(No_arv_parse* no) {
    Expressao* esq = extrai_expNot(no->filhos[0]);
    return extrai_expAndLinha(no->filhos[1], esq);
}
Expressao* extrai_expAndLinha(No_arv_parse* no, Expressao* esq) {
    if (no->filhos.size() == 0) return esq;
    Expressao* dir = extrai_expNot(no->filhos[1]);
    ExpressaoBinaria* bin = new ExpressaoBinaria("And", "and");
    bin->esquerda = esq; bin->direita = dir;
    return extrai_expAndLinha(no->filhos[2], bin);
}

// ---- LÓGICA NOT
Expressao* extrai_expNot(No_arv_parse* no) {
    if (no->filhos.size() == 2) {
        ExpressaoUnaria* un = new ExpressaoUnaria("Not", "not");
        un->expressao = extrai_expNot(no->filhos[1]);
        return un;
    }
    return extrai_expRel(no->filhos[0]); 
}

// ---- RELACIONAL
Expressao* extrai_expRel(No_arv_parse* no) {
    if (no->filhos.size() < 2) return extrai_exp_nivel(no->filhos[0]);
    Expressao* esq = extrai_exp_nivel(no->filhos[0]);
    return extrai_expRelLinha(no->filhos[1], esq);
}
Expressao* extrai_expRelLinha(No_arv_parse* no, Expressao* esq) {
    if (no->filhos.size() == 0) return esq;
    
    string op = no->filhos[0]->simb;
    Expressao* dir = extrai_exp_nivel(no->filhos[1]);
    
    ExpressaoBinaria* bin = nullptr;
    if (op == "EQ") 
        bin = new ExpressaoBinaria("Igualdade", "==");
    else if (op == "NEQ") 
        bin = new ExpressaoBinaria("Diferenca", "~=");
    else if (op == "LESSTHAN") 
        bin = new ExpressaoBinaria("Menor Que", "<");
    else if (op == "LESSEQ") 
        bin = new ExpressaoBinaria("Menor Igual", "<=");
    else if (op == "GREATERTHAN") 
        bin = new ExpressaoBinaria("Maior Que", ">");
    else if (op == "GREATEREQ") 
        bin = new ExpressaoBinaria("Maior Igual", ">=");

    if (bin != nullptr) {
        bin->esquerda = esq;
        bin->direita = dir;
        
        return bin; 
    }
    return esq;
}

// ---- ADIÇÃO E SUBTRAÇÃO
Expressao* extrai_exp_nivel(No_arv_parse* no) {
    Expressao* esq = extrai_termo_nivel(no->filhos[0]);
    return extrai_expLinha(no->filhos[1], esq);
}

Expressao* extrai_expLinha(No_arv_parse* no, Expressao* esq) {
    if (no->filhos.size() == 0) return esq;
    string op = no->filhos[0]->simb;
    Expressao* dir = extrai_termo_nivel(no->filhos[1]);
    
    ExpressaoBinaria* bin = nullptr;
    if (op == "PLUS") bin = new ExpressaoBinaria("Soma", "+");
    else if (op == "MINUS") bin = new ExpressaoBinaria("Subtracao", "-");

    if (bin != nullptr) {
        bin->esquerda = esq;
        bin->direita = dir;
        return extrai_expLinha(no->filhos[2], bin);
    }
    return esq;
}

// ---- MULTIPLICAÇÃO, DIVISÃO E MÓDULO
Expressao* extrai_termo_nivel(No_arv_parse* no) {
    Expressao* esq = Fator::extrai_Fator(no->filhos[0]);
    return extrai_termoLinha(no->filhos[1], esq);
}

Expressao* extrai_termoLinha(No_arv_parse* no, Expressao* esq) {
    if (no->filhos.size() == 0) return esq;
    string op = no->filhos[0]->simb;
    Expressao* dir = Fator::extrai_Fator(no->filhos[1]);
    
    ExpressaoBinaria* bin = nullptr;
    if (op == "MULT") bin = new ExpressaoBinaria("Multiplicacao", "*");
    else if (op == "DIV") bin = new ExpressaoBinaria("Divisao", "/");
    else if (op == "MOD") bin = new ExpressaoBinaria("Modulo", "%");

    if (bin != nullptr) {
        bin->esquerda = esq;
        bin->direita = dir;
        return extrai_termoLinha(no->filhos[2], bin);
    }
    return esq;
}

void Expressao::debug_com_tab(int tab) {}