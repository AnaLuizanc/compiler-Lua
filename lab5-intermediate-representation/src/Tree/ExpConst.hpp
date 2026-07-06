#ifndef _EXP_CONST_HPP_
#define _EXP_CONST_HPP_
#include "Exp.hpp"

class ExpConst : public Exp {
public:
  int valor;
  ExpConst(int v);
  string to_string() override {
    return std::to_string(valor);
  }
};

#endif
