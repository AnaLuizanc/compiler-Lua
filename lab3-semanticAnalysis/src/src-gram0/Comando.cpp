#include "Comando.hpp"
#include "ComandoLocal.hpp"
#include <iostream>
#include "../debug-util.hpp"

// vector<Comando*> Comando::extrai_lista_comandos(No_arv_parse* no) {
//   // LC. 6) LC ->  7) LC -> C LC
//   if (no->regra == 6) return vector<Comando*>();
//   vector<Comando*> res;
//   res.push_back(extrai_comando(no->filhos[0]));
//   vector<Comando*> restante = extrai_lista_comandos(no->filhos[1]);
//   res.insert(res.end(), restante.begin(), restante.end());
//   return res;
// }

Comando* Comando::extrai_comando(No_arv_parse* no) {
  if (no->filhos[0]->simb == "localCmd") {
      No_arv_parse* local = no->filhos[0];
      ComandoLocal* res = new ComandoLocal();
      res->nome = local->filhos[1]->dado_extra;
      res->tipo = Tipo::extrai_Tipo(local->filhos[2]);
      return res;
    }else {
    return NULL;
  }		      
}

void Comando::debug_com_tab(int tab) {
  tab3(tab);
  cerr << "Comando generico"<< endl;
}
