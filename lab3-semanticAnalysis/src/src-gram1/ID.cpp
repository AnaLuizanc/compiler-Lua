// #include "ID.hpp"

// ID* ID::extrai_ID(No_arv_parse* no) {
//   ID* res = new ID();
//   res->nome = no->dado_extra;
//   return res;
// }

#include "ID.hpp"
#include <iostream>

using namespace std;

ID* ID::extrai_ID(No_arv_parse* no) {

    for (int i = 0; i < no->filhos.size(); i++) {
        cout << "filho " << i << ": "
             << no->filhos[i]->simb
             << " | extra = "
             << no->filhos[i]->dado_extra
             << endl;
    }

    ID* res = new ID();
    res->nome = no->dado_extra;
    return res;
}