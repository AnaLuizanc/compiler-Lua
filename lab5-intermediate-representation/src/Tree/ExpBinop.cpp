#include "ExpBinop.hpp"

ExpBinop::ExpBinop(Operador* op, Exp* esq, Exp* dir) {
  this->op = op;
  this->esq = esq;
  this->dir = dir;
}
