#ifndef _STM_RETURN_HPP_
#define _STM_RETURN_HPP_
#include "Stm.hpp"
#include "Exp.hpp"
#include <iostream>

class StmReturn : public Stm {
public:
  Exp* exp_retorno;
  
  StmReturn(Exp* e) {
      exp_retorno = e;
  }
  
  void imprimir() override {
    cout << "RETURN( ";
    if (exp_retorno != nullptr) {
        cout << exp_retorno->to_string();
    }
    cout << " )" << endl;
  }
};
#endif