#ifndef _STM_MOVE_HPP_
#define _STM_MOVE_HPP_
#include "Stm.hpp"
#include "Exp.hpp"

class StmMove : public Stm {
public:
  Exp* destino;
  Exp* origem;
  StmMove(Exp* dst, Exp* org) {
      destino = dst;
      origem = org;
  }
};

#endif
