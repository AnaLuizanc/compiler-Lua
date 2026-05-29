#ifndef _COMANDO_DO_HPP_
#define _COMANDO_DO_HPP_

#include "Comando.hpp"
#include <vector>

class ComandoDo : public Comando {
public:
    std::vector<Comando*> bloco;

    void debug_com_tab(int tab) override;
};

#endif