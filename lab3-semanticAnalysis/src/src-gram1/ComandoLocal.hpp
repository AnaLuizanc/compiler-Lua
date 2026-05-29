#ifndef _COMANDO_LOCAL_HPP_
#define _COMANDO_LOCAL_HPP_
#include <string>
#include "Comando.hpp"
#include "Tipo.hpp"

using namespace std;

class ComandoLocal : public Comando {
public:
  string nome;
  Tipo* tipo;

  ComandoLocal() { tipo = NULL; }

  void debug_com_tab(int tab) override; 
};
#endif