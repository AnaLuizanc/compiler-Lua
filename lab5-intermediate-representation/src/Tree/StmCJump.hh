#ifndef _STM_CJUMP_HPP_
#define _STM_CJUMP_HPP_
#include "Stm.hpp"
#include "Exp.hpp"
#include<string>
using namespace std;

class StmCJump : public Stm {
public:
  Exp* expressao_booleana;
  string destino_verdade;
  string destino_falso;
  
  StmCJump(Exp* exp, string v, string f) {
    expressao_booleana = exp;
    destino_verdade = v;
    destino_falso = f;
  }

  void imprimir() override {
    cout << "CJUMP( ";
    
    if (expressao_booleana != nullptr) {
        cout << expressao_booleana->to_string();
    } else {
        cout << "NULL_EXP";
    }
    
    cout << ", " << destino_verdade << ", " << destino_falso << " )" << endl;
}
};

#endif
