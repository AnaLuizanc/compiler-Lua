#ifndef _STM_JUMP_HPP_
#define _STM_JUMP_HPP_
#include "Stm.hpp"
#include "Exp.hpp"
#include<vector>
#include<string>
using namespace std;

class StmJump : public Stm {
public:
  Exp* destino = nullptr;
  vector<string> alvos;
  
  StmJump(string alvo) {
    alvos.push_back(alvo);
  }

  void imprimir() override {
    cout << "JUMP( " << alvos[0] << " )" << endl;
  }
};

#endif
