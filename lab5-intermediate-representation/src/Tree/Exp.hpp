#ifndef _EXP_HPP_
#define _EXP_HPP_

#include <string>
using namespace std;

class Expressao;

class Exp {
public:
  Exp(){}
  virtual string to_string() { return ""; } 
  virtual ~Exp() {}
};

#endif
