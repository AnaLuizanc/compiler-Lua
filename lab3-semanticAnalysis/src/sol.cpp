#include <algorithm>
#include<vector>
#include<string>
#include<iostream>
#include <fstream>   
#include<sstream>
#include<map>
#include<stack>
using namespace std;

#include "Gramatica.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"
#include "Funcao.hpp"
#include "src-gram1/AnalisadorSemantico.hpp"


int main(int argc, char * argv[]) {
  if (argc < 3) {
    cerr << "Parametros nomes dos arquivos: 1) csv com gramática e 2) csv com tabela LR1" << endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1;
  if (argc == 1) {
    //cerr << "Valores padrao utilizados: gramatica9.site e tabela_lr1.conf" << endl;
    nome_gramatica = string("gramatica-1.site");
    nome_tab_lr1 = string("tabela_lr1.conf");
  } else {
    nome_gramatica = string(argv[1]);
    nome_tab_lr1 = string(argv[2]);
  }

  ifstream arq_gramatica(nome_gramatica);
  ifstream arq_tabela_lr1(nome_tab_lr1);
  if (arq_tabela_lr1.fail() || arq_gramatica.fail()) {
    cerr << "Falha ao abrir arquivos: " <<
      ((arq_gramatica.fail()) ? nome_gramatica : "") << ", " <<
      ((arq_tabela_lr1.fail()) ? nome_tab_lr1 : "") << endl;
    return 1;
  }
  Parser parser(arq_gramatica, arq_tabela_lr1);
  parser.tabela.debug();
  parser.gram.debug();


  Arvore_parse arv = parser.executa_parse(cin);
  cerr << "Parse executado" << endl;
  arv.debug();

  if(arv.raiz == nullptr) {
    cerr << "Erro: arvore de parse vazia" << endl;
    return 1;
  }
  Funcao* func = Funcao::extrai_funcao(arv.raiz);
    
    if (func != nullptr) {
        func->debug();
        
        vector<string> argumentos_linha_comando;
        for (int i = 3; i < argc; ++i) { 
            argumentos_linha_comando.push_back(argv[i]);
        }
        
        AnalisadorSemantico analisador;
        analisador.analisar(func, argumentos_linha_comando);
        
        if (analisador.ultimo_valor != nullptr) {
            analisador.ultimo_valor->imprimir();
        }
    }
    
  return 0;
}
