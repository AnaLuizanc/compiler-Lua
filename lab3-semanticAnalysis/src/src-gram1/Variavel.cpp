#include "Variavel.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

vector<Variavel*> Variavel::extrai_lista_parametros(No_arv_parse* no) {
  vector<Variavel*> res;

  if (no == NULL)
    return res;

  // params -> param pL
  res.push_back(extrai_variavel_P(no->filhos[0]));

  vector<Variavel*> resto =
      extrai_lista_nao_vazia_parametros(no->filhos[1]);

  res.insert(res.end(), resto.begin(), resto.end());

  return res;
}

vector<Variavel*> Variavel::extrai_lista_nao_vazia_parametros(No_arv_parse* no) {
  vector<Variavel*> res;

  if (no == NULL)
    return res;

  // pL -> ε
  if (no->filhos.size() == 0)
    return res;

  // pL -> COMMA param pL
  res.push_back(extrai_variavel_P(no->filhos[1]));

  vector<Variavel*> resto =
      extrai_lista_nao_vazia_parametros(no->filhos[2]);

  res.insert(res.end(), resto.begin(), resto.end());

  return res;
}

Variavel* Variavel::extrai_variavel_P(No_arv_parse* no) {
  Variavel* res = new Variavel();

  // param -> ID tipoId
  res->nome = ID::extrai_ID(no->filhos[0]);
  res->tipo = Tipo::extrai_Tipo(no->filhos[1]);

  return res;
}

void Variavel::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "[" << nome->nome << ":" 
       << (tipo == NULL ? "TIPO_INVALIDO" : tipo->nome())
       << "] Variavel Declarada" << endl;
}