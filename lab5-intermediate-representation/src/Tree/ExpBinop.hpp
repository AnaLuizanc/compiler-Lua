#ifndef _EXP_BINOP_HPP_
#define _EXP_BINOP_HPP_
#include "Exp.hpp"
#include "Operador.hpp"

class ExpBinop : public Exp {
public:
  Operador* op;
  Exp* esq;
  Exp* dir;
  ExpBinop(Operador* op, Exp* esq, Exp* dir);
  string to_string() override {
    return "BINOP(" + op->to_string() + ", " + esq->to_string() + ", " + dir->to_string() + ")";
  }
};

#endif
