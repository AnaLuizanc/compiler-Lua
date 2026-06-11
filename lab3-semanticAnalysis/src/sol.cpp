#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>   
#include <sstream>
#include <map>
#include <stack>
using namespace std;

#include "Gramatica.hpp"
#include "TabelaLR1.hpp"
#include "Arvore.hpp"
#include "Parser.hpp"
#include "Funcao.hpp"
#include "src-gram1/AnalisadorSemantico.hpp"
#include "../lab4-frame/FrameFuncao.hpp" 

int main(int argc, char * argv[]) {
  if (argc < 3) {
    cerr << "Parametros nomes dos arquivos: 1) csv com gramática e 2) csv com tabela LR1" << endl;
    return 1;
  }
  string nome_gramatica, nome_tab_lr1;
  if (argc == 1) {
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

  Arvore_parse arv = parser.executa_parse(cin);
  cerr << "Parse executado" << endl;
  arv.debug();

  if(arv.raiz == nullptr) {
    cerr << "Erro: arvore de parse vazia" << endl;
    return 1;
  }
  
  Funcao* func = Funcao::extrai_funcao(arv.raiz);
    
  if (func != nullptr) {
      cerr << "\n=== ARVORE SINTATICA (AST) ===" << endl;
      func->debug();
      
      // TESTE DO LAB 4: GERAÇÃO DO FRAME
      FrameFuncao* frame = FrameFuncao::gera_frame_de_funcao(func);
      
      if (frame != nullptr) {
          cout << "\n======= INFORMACOES DO FRAME (LAB 4) =======" << endl;
          cout << "Tamanho total do frame: " << frame->tamanho_frame << " bytes" << endl;
          cout << "Parametros de entrada: " << frame->n_param_entrada << endl;
          cout << "Maximo de parametros de saida: " << frame->n_maximo_param_saida << endl;
          cout << "Variaveis alocadas na memoria (Frame): " << frame->n_variaveis_no_frame << endl;
          cout << "Variaveis em pseudo-registradores (Temp): " << frame->n_pseudo_registradores << endl;
          cout << "============================================\n" << endl;
      }
      // ==========================================================
        
      vector<string> argumentos_linha_comando;
      for (int i = 3; i < argc; ++i) { 
          argumentos_linha_comando.push_back(argv[i]);
      }
        
      AnalisadorSemantico analisador;
      analisador.analisar(func, argumentos_linha_comando);
        
      if (analisador.ultimo_valor != nullptr) {
          cout << "Resultado final: ";
          analisador.ultimo_valor->imprimir();
      }
  }
    
  return 0;
}