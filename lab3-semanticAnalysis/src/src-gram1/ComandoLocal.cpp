#include "ComandoLocal.hpp"
#include <iostream>
#include "../debug-util.hpp"

using namespace std;

void ComandoLocal::debug() {
  cerr << "local " << nome;

  if (tipo != NULL) {
    cerr << ":" << tipo->nome();
  }

  cerr << endl;
}