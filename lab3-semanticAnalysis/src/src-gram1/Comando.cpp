#include "Comando.hpp"
// #include "ComandoAtribuicao.hpp"
// #include "ComandoDeclaracao.hpp"
// #include "ComandoRetorno.hpp"
#include "ID.hpp"
#include "Tipo.hpp"
#include "Variavel.hpp"
#include "Expressao.hpp"

#include <iostream>
#include "../debug-util.hpp"

using namespace std;

vector<Comando *> Comando::extrai_lista_comandos(No_arv_parse *no)
{
  vector<Comando *> res;

  if (no == NULL)
    return res;

  // 10 listaCmd -> cmd
  if (no->regra == 10)
  {
    res.push_back(extrai_comando(no->filhos[0]));
    return res;
  }

  // 11 listaCmd -> cmd listaCmd
  if (no->regra == 11)
  {
    res.push_back(extrai_comando(no->filhos[0]));

    vector<Comando *> restante =
        extrai_lista_comandos(no->filhos[1]);

    res.insert(res.end(), restante.begin(), restante.end());
  }

  return res;
}

Comando *Comando::extrai_comando(No_arv_parse *no)
{
  if (no == NULL)
    return NULL;

  /*
    12 cmd -> cmdLocal
    13 cmd -> atribuicao
    14 cmd -> retorno
  */

  // if (no->regra == 12)
  // {
  //   ComandoDeclaracao *res = new ComandoDeclaracao();

  //   Variavel *v = new Variavel();
  //   v->nome = ID::extrai_ID(no->filhos[0]->filhos[1]);
  //   v->tipo = Tipo::extrai_Tipo(no->filhos[0]->filhos[2]);

  //   res->variavel = v;
  //   return res;
  // }

  // else if (no->regra == 13)
  // {
  //   ComandoAtribuicao *res = new ComandoAtribuicao();

  //   res->esquerda = ID::extrai_ID(no->filhos[0]->filhos[0]);
  //   res->direita = Expressao::extrai_expressao(
  //       no->filhos[0]->filhos[2]);

  //   return res;
  // }

  // else if (no->regra == 14)
  // {
  //   ComandoRetorno *res = new ComandoRetorno();

  //   res->expressao =
  //       Expressao::extrai_expressao(
  //           no->filhos[0]->filhos[1]);

  //   return res;
  // }

  return NULL;
}

void Comando::debug_com_tab(int tab)
{
  tab3(tab);
  cerr << "Comando generico" << endl;
}