#include "Funcao.hpp"
#include "Comando.hpp"
#include "../debug-util.hpp"
#include <iostream>

Funcao::Funcao() {
}

Funcao* Funcao::extrai_funcao(No_arv_parse *no) {
    if (no->regra != 1)   return NULL;

    Funcao* res = new Funcao();
    res->nome_funcao = ID::extrai_ID(no->filhos[1]);
    res->parametros = Variavel::extrai_lista_parametros(no->filhos[3]);
    res->tipo_retorno = Tipo::extrai_Tipo(no->filhos[5]);
    res->comandos = Comando::extrai_lista_comandos(no->filhos[6]);
    return res;
}

void debug_comandos(const vector<Comando*> &coms, int tab) {
    for (int ic = 0; ic < coms.size(); ++ic) 
        coms[ic]->debug_com_tab(tab+1);  
}

void Funcao::debug() {
    if (tipo_retorno == NULL) cerr<< "TR NULL"<< endl;
    if (nome_funcao == NULL) cerr<< "NF NULL"<< endl;
    
    string ret = (tipo_retorno != NULL) ? tipo_retorno->nome() : "NULL";
    string nom = (nome_funcao != NULL) ? nome_funcao->nome : "NULL";
    
    cerr << "Funcao:[retorno=" << ret << "][nome=" << nom << "]" << endl;
    cerr << "      (Param:(";
    fflush(stderr);
    for (int i_par = 0; i_par < parametros.size(); ++i_par) {
        cerr << ((parametros[i_par])->tipo == NULL ? "TIPO_INVALIDO" : (parametros[i_par])->tipo->nome()) << " " <<
        (parametros[i_par])->nome->nome << ", ";
    }
    cerr << ") { " << endl;
    debug_comandos(comandos, 1);
    cerr << "}" <<  endl;
}

extern Stm* sequenciar_lista_comandos(const vector<Comando*>& cmds);

Stm* Funcao::gerar_IR() {
    return sequenciar_lista_comandos(this->comandos);
}
