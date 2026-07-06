#ifndef _STM_SEQ_HPP_
#define _STM_SEQ_HPP_
#include "Stm.hpp"

class StmSeq : public Stm {
public:
  Stm* esq;
  Stm* dir;
  StmSeq(Stm* e, Stm* d) {
    esq = e;
    dir = d;
  }

  void imprimir() override {
    if (esq != nullptr) esq->imprimir();
    if (dir != nullptr) dir->imprimir();
  }
};

#endif
