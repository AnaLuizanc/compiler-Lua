#ifndef _EXP_TEMP_HPP_
#define _EXP_TEMP_HPP_
#include "Exp.hpp"
#include "../src-gram1/Expressao.hpp"

class ExpTemp : public Exp {
public:
  int id;
  ExpTemp(int id);
};

#endif
