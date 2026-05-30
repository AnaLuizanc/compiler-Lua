#include "AnalisadorSemantico.hpp"
#include "Execucao.hpp"
#include "ComandoLocal.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoDo.hpp"
#include <iostream>

using namespace std;

void AnalisadorSemantico::analisar(Funcao* func) {
    if (func == nullptr) return;

    Execucao exec;
    retorno_esperado = func->tipo_retorno;

    int valor_teste_int = 10;
    float valor_teste_float = 10.5f;

    for (Variavel* param : func->parametros) {
        if (!amb.declarar_variavel(param->nome->nome, param->tipo)) {
            cerr << "Erro Semantico: Parametro '" << param->nome->nome << "' repetido." << endl;
            exit(1);
        }

        if (param->tipo->valor == Tipo::INT) {
            exec.definir(param->nome->nome, new Valor(valor_teste_int));
            valor_teste_int = 3; 
        }
        else if (param->tipo->valor == Tipo::FLOAT) exec.definir(param->nome->nome, new Valor(valor_teste_float));
        else if (param->tipo->valor == Tipo::BOOL) exec.definir(param->nome->nome, new Valor(true));
    }


    validar_comandos(func->comandos, exec);

    cout << "\n=============================================" << endl;
    cout << "SUCESSO: Analise Semantica concluida sem erros!" << endl;
    cout << "=============================================" << endl;
}

void AnalisadorSemantico::validar_comandos(const std::vector<Comando*>& comandos, Execucao& exec) {
    for (Comando* cmd : comandos) {
        
        // Regra 1: Declaracao de Variavel Local
        if (ComandoLocal* cmdLocal = dynamic_cast<ComandoLocal*>(cmd)) {
            if (!amb.declarar_variavel(cmdLocal->nome, cmdLocal->tipo)) {
                cerr << "Erro Semantico: Variavel local '" << cmdLocal->nome 
                     << "' ja declarada neste escopo." << endl;
                exit(1);
            }
            if (cmdLocal->tipo->valor == Tipo::INT) exec.definir(cmdLocal->nome, new Valor(0));
            else if (cmdLocal->tipo->valor == Tipo::FLOAT) exec.definir(cmdLocal->nome, new Valor(0.0f));
            else if (cmdLocal->tipo->valor == Tipo::BOOL) exec.definir(cmdLocal->nome, new Valor(false));
        
        }
        
        // Regra 2: Atribuicao de Valor
        else if (ComandoAtribuicao* cmdAtrib = dynamic_cast<ComandoAtribuicao*>(cmd)) {
            Tipo* tipo_var = amb.buscar_variavel(cmdAtrib->esquerda->nome);
            if (tipo_var == nullptr) {
                cerr << "Erro Semantico: Tentativa de atribuicao a variavel '" 
                     << cmdAtrib->esquerda->nome << "' nao declarada." << endl;
                exit(1);
            }

            Tipo* tipo_exp = cmdAtrib->direita->inferir_tipo(amb);
            
            // Compara os valores (INT vs BOOL, etc)
            if (tipo_exp != nullptr && tipo_var->valor != tipo_exp->valor) {
                cerr << "Erro Semantico: Atribuicao invalida. A variavel '" 
                     << cmdAtrib->esquerda->nome << "' e do tipo " << tipo_var->nome() 
                     << ", mas a expressao resulta em " << tipo_exp->nome() << "." << endl;
                exit(1);
            }

            Valor* res = cmdAtrib->direita->avaliar(exec);
            exec.definir(cmdAtrib->esquerda->nome, res);
            ultimo_valor = res;
        }
        
        // Regra 3: Retorno de Funcao
        else if (ComandoRetorno* cmdRet = dynamic_cast<ComandoRetorno*>(cmd)) {
            Tipo* tipo_exp = cmdRet->expressao->inferir_tipo(amb);
            
            if (tipo_exp != nullptr && retorno_esperado->valor != tipo_exp->valor) {
                cerr << "Erro Semantico: O tipo retornado (" << tipo_exp->nome() 
                     << ") nao corresponde a assinatura da funcao (" 
                     << retorno_esperado->nome() << ")." << endl;
                exit(1);
            }
        }
        
        // Regra 4: Novo Bloco de Escopo (DO ... END)
        else if (ComandoDo* cmdDo = dynamic_cast<ComandoDo*>(cmd)) {
            amb.entrar_escopo(); 
            exec.entrar(); // A memória de execução também ganha um novo escopo
            
            validar_comandos(cmdDo->bloco, exec); 
            
            exec.sair(); // Limpa as variáveis da memória ao sair do bloco
            amb.sair_escopo();   
        }
    }
}