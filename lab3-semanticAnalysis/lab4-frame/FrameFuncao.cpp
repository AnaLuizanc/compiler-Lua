#include "FrameFuncao.hpp"
#include "FrameAcessoNoFrame.hpp"
#include "FrameAcessoTemp.hpp"

#include "../src-gram1/ComandoLocal.hpp"
#include "../src-gram1/ComandoAtribuicao.hpp"
#include "../src-gram1/ComandoIf.hpp"
#include "../src-gram1/ComandoWhile.hpp"
#include "../src-gram1/ComandoDo.hpp"
#include "../src-gram1/ComandoRetorno.hpp"
#include "../src-gram1/ExpressaoBinaria.hpp"
#include "../src-gram1/ExpressaoUnaria.hpp"
#include "../src-gram1/ExpressaoOr.hpp"
#include "../src-gram1/Fator.hpp"
#include "../src-gram1/ExpressaoChamada.hpp" 

#include <map>
#include <string>

using namespace std;

FrameFuncao::FrameFuncao() {
    tamanho_frame = 0;
    n_param_entrada = 0;
    n_maximo_param_saida = 0;
    n_pseudo_registradores = 0;
    n_variaveis_no_frame = 0;
}

void analisar_expressao(Expressao* exp, map<string, bool>& var_precisa_frame, int& max_param_saida, bool em_parametro) {
    if (exp == nullptr) return;

    if (auto bin = dynamic_cast<ExpressaoBinaria*>(exp)) {
        analisar_expressao(bin->esquerda, var_precisa_frame, max_param_saida, em_parametro);
        analisar_expressao(bin->direita, var_precisa_frame, max_param_saida, em_parametro);
    } 
    else if (auto un = dynamic_cast<ExpressaoUnaria*>(exp)) {
        analisar_expressao(un->expressao, var_precisa_frame, max_param_saida, em_parametro);
    } 
    else if (auto or_exp = dynamic_cast<ExpressaoOr*>(exp)) {
        analisar_expressao(or_exp->raiz, var_precisa_frame, max_param_saida, em_parametro);
    } 
    else if (auto chamada = dynamic_cast<ExpressaoChamada*>(exp)) {
        int qtd_argumentos = chamada->argumentos.size();
        if (qtd_argumentos > max_param_saida) {
            max_param_saida = qtd_argumentos;
        }
        for (auto arg : chamada->argumentos) {
            analisar_expressao(arg, var_precisa_frame, max_param_saida, true); 
        }
    }
    else if (auto fator = dynamic_cast<Fator*>(exp)) {
        if (fator->interno) {
            analisar_expressao(fator->interno, var_precisa_frame, max_param_saida, em_parametro);
        } else {
            if (em_parametro && var_precisa_frame.find(fator->valor) != var_precisa_frame.end()) {
                var_precisa_frame[fator->valor] = true; 
            }
        }
    }
}

void analisar_comandos(const vector<Comando*>& comandos, map<string, bool>& var_precisa_frame, int& max_param_saida) {
    for (Comando* cmd : comandos) {
        if (auto cmdLocal = dynamic_cast<ComandoLocal*>(cmd)) {
            var_precisa_frame[cmdLocal->nome] = false; 
        } 
        else if (auto cmdAtrib = dynamic_cast<ComandoAtribuicao*>(cmd)) {
            analisar_expressao(cmdAtrib->direita, var_precisa_frame, max_param_saida, false);
        } 
        else if (auto cmdIf = dynamic_cast<ComandoIf*>(cmd)) {
            analisar_expressao(cmdIf->condicao, var_precisa_frame, max_param_saida, false);
            analisar_comandos(cmdIf->blocoVerdadeiro, var_precisa_frame, max_param_saida);
            analisar_comandos(cmdIf->blocoFalso, var_precisa_frame, max_param_saida);
        } 
        else if (auto cmdWhile = dynamic_cast<ComandoWhile*>(cmd)) {
            analisar_expressao(cmdWhile->condicao, var_precisa_frame, max_param_saida, false);
            analisar_comandos(cmdWhile->bloco, var_precisa_frame, max_param_saida);
        } 
        else if (auto cmdDo = dynamic_cast<ComandoDo*>(cmd)) {
            analisar_comandos(cmdDo->bloco, var_precisa_frame, max_param_saida);
        } 
        else if (auto cmdRet = dynamic_cast<ComandoRetorno*>(cmd)) {
            analisar_expressao(cmdRet->expressao, var_precisa_frame, max_param_saida, false);
        }
    }
}

void vincular_acessos_exp(Expressao* exp, map<string, FrameAcesso*>& tabela_acessos) {
    if (exp == nullptr) return;

    if (auto bin = dynamic_cast<ExpressaoBinaria*>(exp)) {
        vincular_acessos_exp(bin->esquerda, tabela_acessos);
        vincular_acessos_exp(bin->direita, tabela_acessos);
    } 
    else if (auto un = dynamic_cast<ExpressaoUnaria*>(exp)) {
        vincular_acessos_exp(un->expressao, tabela_acessos);
    } 
    else if (auto or_exp = dynamic_cast<ExpressaoOr*>(exp)) {
        vincular_acessos_exp(or_exp->raiz, tabela_acessos);
    } 
    else if (auto chamada = dynamic_cast<ExpressaoChamada*>(exp)) {
        for (auto arg : chamada->argumentos) {
            vincular_acessos_exp(arg, tabela_acessos);
        }
    }
    else if (auto fator = dynamic_cast<Fator*>(exp)) {
        if (fator->interno) {
            vincular_acessos_exp(fator->interno, tabela_acessos);
        } else {
            if (tabela_acessos.find(fator->valor) != tabela_acessos.end()) {
                fator->acesso_frame = tabela_acessos[fator->valor];
            }
        }
    }
}

void vincular_acessos_cmd(const vector<Comando*>& comandos, map<string, FrameAcesso*>& tabela_acessos) {
    for (Comando* cmd : comandos) {
        if (auto cmdAtrib = dynamic_cast<ComandoAtribuicao*>(cmd)) {
            vincular_acessos_exp(cmdAtrib->direita, tabela_acessos);
        } else if (auto cmdIf = dynamic_cast<ComandoIf*>(cmd)) {
            vincular_acessos_exp(cmdIf->condicao, tabela_acessos);
            vincular_acessos_cmd(cmdIf->blocoVerdadeiro, tabela_acessos);
            vincular_acessos_cmd(cmdIf->blocoFalso, tabela_acessos);
        } else if (auto cmdWhile = dynamic_cast<ComandoWhile*>(cmd)) {
            vincular_acessos_exp(cmdWhile->condicao, tabela_acessos);
            vincular_acessos_cmd(cmdWhile->bloco, tabela_acessos);
        } else if (auto cmdDo = dynamic_cast<ComandoDo*>(cmd)) {
            vincular_acessos_cmd(cmdDo->bloco, tabela_acessos);
        } else if (auto cmdRet = dynamic_cast<ComandoRetorno*>(cmd)) {
            vincular_acessos_exp(cmdRet->expressao, tabela_acessos);
        }
    }
}

FrameFuncao* FrameFuncao::gera_frame_de_funcao(Funcao* fun) {
    if (fun == nullptr) return nullptr;

    FrameFuncao* frame = new FrameFuncao();
    map<string, FrameAcesso*> tabela_acessos;

    frame->n_param_entrada = fun->parametros.size();
    int offset_param = 8;
    for (auto param : fun->parametros) {
        FrameAcessoNoFrame* acesso = new FrameAcessoNoFrame();
        acesso->posicao_no_frame = offset_param;
        offset_param += 8;
        tabela_acessos[param->nome->nome] = acesso; 
    }

    map<string, bool> var_precisa_frame;
    analisar_comandos(fun->comandos, var_precisa_frame, frame->n_maximo_param_saida);

    int offset_local = -40; 
    int id_temp = 1;        

    for (const auto& par : var_precisa_frame) {
        string nome_var = par.first;
        bool escapa = par.second;

        if (escapa) { 
            FrameAcessoNoFrame* acesso = new FrameAcessoNoFrame();
            acesso->posicao_no_frame = offset_local;
            offset_local -= 8;
            frame->n_variaveis_no_frame++;
            tabela_acessos[nome_var] = acesso;
        } else {      
            FrameAcessoTemp* acesso = new FrameAcessoTemp();
            acesso->id = id_temp++;
            frame->n_pseudo_registradores++;
            tabela_acessos[nome_var] = acesso;
        }
    }

    frame->tamanho_frame = 40 + (frame->n_variaveis_no_frame * 8);

    vincular_acessos_cmd(fun->comandos, tabela_acessos);

    return frame;
}