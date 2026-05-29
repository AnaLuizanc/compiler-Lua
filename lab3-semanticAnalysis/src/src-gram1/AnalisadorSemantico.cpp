#include "AnalisadorSemantico.hpp"
#include "ComandoLocal.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoDo.hpp"
#include <iostream>

using namespace std;

void AnalisadorSemantico::analisar(Funcao* func) {
    if (func == nullptr) return;

    // Guardamos qual é o tipo que a função promete retornar (ex: int, bool)
    retorno_esperado = func->tipo_retorno;

    // O escopo global da função já foi criado no construtor da TabelaSimbolos, 
    // mas vamos garantir que os parâmetros entram como variáveis declaradas
    for (Variavel* param : func->parametros) {
        if (!amb.declarar_variavel(param->nome->nome, param->tipo)) {
            cerr << "Erro Semantico: Parametro '" << param->nome->nome << "' repetido." << endl;
            exit(1);
        }
    }

    // Inicia a validação da lista de comandos da função
    validar_comandos(func->comandos);

    cout << "\n=============================================" << endl;
    cout << "SUCESSO: Analise Semantica concluida sem erros!" << endl;
    cout << "=============================================" << endl;
}

void AnalisadorSemantico::validar_comandos(const std::vector<Comando*>& comandos) {
    for (Comando* cmd : comandos) {
        
        // Regra 1: Declaracao de Variavel Local
        if (ComandoLocal* cmdLocal = dynamic_cast<ComandoLocal*>(cmd)) {
            if (!amb.declarar_variavel(cmdLocal->nome, cmdLocal->tipo)) {
                cerr << "Erro Semantico: Variavel local '" << cmdLocal->nome 
                     << "' ja declarada neste escopo." << endl;
                exit(1);
            }
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
            amb.entrar_escopo(); // Cria um sub-ambiente (shadowing)
            validar_comandos(cmdDo->bloco); // Chamada recursiva para os comandos internos
            amb.sair_escopo();   // Destroi as variáveis locais deste bloco ao sair
        }
    }
}