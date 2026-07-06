#ifndef _EXP_MEM_HPP_
#define _EXP_MEM_HPP_
#include "Exp.hpp"
#include "../src-gram1/Expressao.hpp"

class ExpMem : public Exp {
public:
  Exp* endereco;
  ExpMem(Exp* endereco);
  string to_string() override {
    return "MEM(" + endereco->to_string() + ")";
  }
};

#endif
