#ifndef _EXP_HPP_
#define _EXP_HPP_
using namespace std;

class Expressao;

class Exp {
public:
  Exp();
  static Exp* gera_Exp_de_Expressao(Expressao* e);
};

#endif
