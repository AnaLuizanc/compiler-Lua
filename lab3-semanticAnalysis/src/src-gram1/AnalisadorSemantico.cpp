#include "AnalisadorSemantico.hpp"
#include "Execucao.hpp"
#include "ComandoLocal.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoDo.hpp"
#include "ComandoIf.hpp"
#include "ComandoWhile.hpp"
#include <iostream>
using namespace std;

void AnalisadorSemantico::analisar(Funcao* func, const vector<string>& args) {
    if (func == nullptr) return;

    Execucao exec;
    retorno_esperado = func->tipo_retorno;

    int arg_idx = 0; 

    for (Variavel* param : func->parametros) {
        if (!amb.declarar_variavel(param->nome->nome, param->tipo)) {
            cerr << "Erro Semantico: Parametro '" << param->nome->nome << "' repetido." << endl;
            exit(1);
        }
        
        string valor_str = (arg_idx < args.size()) ? args[arg_idx] : "0";
        arg_idx++;

        try {
            if (param->tipo->valor == Tipo::INT) {
                exec.definir(param->nome->nome, new Valor(stoi(valor_str)));
            }
            else if (param->tipo->valor == Tipo::FLOAT) {
                exec.definir(param->nome->nome, new Valor(stof(valor_str)));
            }
            else if (param->tipo->valor == Tipo::BOOL) {
                bool b = (valor_str == "true" || valor_str == "1");
                exec.definir(param->nome->nome, new Valor(b));
            }
        } catch (...) {
            if (param->tipo->valor == Tipo::INT) exec.definir(param->nome->nome, new Valor(0));
            else if (param->tipo->valor == Tipo::FLOAT) exec.definir(param->nome->nome, new Valor(0.0f));
            else if (param->tipo->valor == Tipo::BOOL) exec.definir(param->nome->nome, new Valor(false));
        }
    }

    validar_comandos(func->comandos, exec);

    cout << "\n===============================================" << endl;
    cout << "SUCESSO: Analise Semantica concluida sem erros!" << endl;
    cout << "===============================================" << endl;
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
            if (cmdLocal->tipo->valor == Tipo::INT) 
                exec.definir(cmdLocal->nome, new Valor(0));
            else if (cmdLocal->tipo->valor == Tipo::FLOAT)
                exec.definir(cmdLocal->nome, new Valor(0.0f));
            else if (cmdLocal->tipo->valor == Tipo::BOOL) 
                exec.definir(cmdLocal->nome, new Valor(false));
        }
        else if (ComandoAtribuicao* cmdAtrib = dynamic_cast<ComandoAtribuicao*>(cmd)) {// Regra 2: Atribuicao de Valor
            Tipo* tipo_var = amb.buscar_variavel(cmdAtrib->esquerda->nome);
            if (tipo_var == nullptr) {
                cerr << "Erro Semantico: Tentativa de atribuicao a variavel '" 
                     << cmdAtrib->esquerda->nome << "' nao declarada." << endl;
                exit(1);
            }

            Tipo* tipo_exp = cmdAtrib->direita->inferir_tipo(amb);
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
        else if (ComandoRetorno* cmdRet = dynamic_cast<ComandoRetorno*>(cmd)) {// Regra 3: Retorno de Funcao
            Tipo* tipo_exp = cmdRet->expressao->inferir_tipo(amb);
            
            if (tipo_exp != nullptr && retorno_esperado->valor != tipo_exp->valor) {
                cerr << "Erro Semantico: O tipo retornado (" << tipo_exp->nome() 
                     << ") nao corresponde a assinatura da funcao (" 
                     << retorno_esperado->nome() << ")." << endl;
                exit(1);
            }

            Valor* res = cmdRet->expressao->avaliar(exec);
            ultimo_valor = res;
        }
        else if (ComandoDo* cmdDo = dynamic_cast<ComandoDo*>(cmd)) {// Regra 4: Novo Bloco de Escopo (DO ... END)
            amb.entrar_escopo(); 
            exec.entrar(); 
            validar_comandos(cmdDo->bloco, exec); 
            exec.sair(); 
            amb.sair_escopo();   
        }
        else if (ComandoIf* cmdIf = dynamic_cast<ComandoIf*>(cmd)) {// Regra 5: Estrutura Condicional (IF-THEN-ELSE)
            Tipo* tipo_cond = cmdIf->condicao->inferir_tipo(amb);
            if (tipo_cond == nullptr || tipo_cond->valor != Tipo::BOOL) {
                cerr << "Erro Semantico: A condicao do 'if' deve resultar num booleano." << endl;
                exit(1);
            }

            Valor* cond = cmdIf->condicao->avaliar(exec);
            if (cond->dados.b) {
                amb.entrar_escopo(); exec.entrar();
                validar_comandos(cmdIf->blocoVerdadeiro, exec);
                exec.sair(); amb.sair_escopo();
            } 
            else if (!cmdIf->blocoFalso.empty()) {
                amb.entrar_escopo(); exec.entrar();
                validar_comandos(cmdIf->blocoFalso, exec);
                exec.sair(); amb.sair_escopo();
            }
        }
        else if (ComandoWhile* cmdWhile = dynamic_cast<ComandoWhile*>(cmd)) {// Regra 6: Estrutura de Repetição (WHILE)
            Tipo* tipo_cond = cmdWhile->condicao->inferir_tipo(amb);
            if (tipo_cond == nullptr || tipo_cond->valor != Tipo::BOOL) {
                cerr << "Erro Semantico: A condicao do 'while' deve resultar num booleano." << endl;
                exit(1);
            }

            while (true) {
                Valor* cond = cmdWhile->condicao->avaliar(exec);
                if (!cond->dados.b) break; 
                amb.entrar_escopo(); exec.entrar();
                validar_comandos(cmdWhile->bloco, exec);
                exec.sair(); amb.sair_escopo();
            }
        }
    }
}