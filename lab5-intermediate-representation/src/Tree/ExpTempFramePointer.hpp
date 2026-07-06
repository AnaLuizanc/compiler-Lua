#ifndef _EXP_TEMPFRAMEPOINTER_HPP_
#define _EXP_TEMPFRAMEPOINTER_HPP_
#include "Exp.hpp"
#include "ExpTemp.hpp"

class ExpTempFramePointer : public ExpTemp {
public:
  ExpTempFramePointer();
  string to_string() override {
    return "FP";
  }
};

#endif
