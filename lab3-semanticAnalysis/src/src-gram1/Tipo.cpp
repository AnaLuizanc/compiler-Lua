#include "Tipo.hpp"
#include <algorithm>

Tipo::Tipo(Valor valor) {
    this->valor = valor;
}

string Tipo::nome() const {
    switch(valor) {
    case INT:
        return "INT";
    case FLOAT:
        return "FLOAT";
    case BOOL:
        return "BOOL";
    }
    return "";
}

Tipo* Tipo::extrai_Tipo(No_arv_parse* no) {
    if (no == NULL) return NULL;

    string nome = no->filhos[1]->dado_extra;
    transform(nome.begin(), nome.end(), nome.begin(), ::tolower);

    if (nome == "int")
        return new Tipo(INT);
    if (nome == "float")
        return new Tipo(FLOAT);
    if (nome == "bool")
        return new Tipo(BOOL);

    return NULL;
}
