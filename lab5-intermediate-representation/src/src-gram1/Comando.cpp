#include "Comando.hpp"
#include "ComandoLocal.hpp"
#include "ComandoAtribuicao.hpp"
#include "ComandoRetorno.hpp"
#include "ComandoDo.hpp"
#include "ComandoIf.hpp"
#include "ComandoWhile.hpp"
#include "ID.hpp"
#include "Tipo.hpp"
#include "Expressao.hpp"
#include "../Tree/Stm.hpp"

#include <iostream>
#include "../debug-util.hpp"

using namespace std;

vector<Comando *> Comando::extrai_lista_comandos(No_arv_parse *no) {
    vector<Comando *> res;
    if (no == NULL) return res;

    if (no->simb == "bloco")
        return extrai_lista_comandos(no->filhos[0]);

    if (no->simb == "listaCmd") {
        // listaCmd -> cmd
        if (no->filhos.size() == 1) {
            Comando* c = extrai_comando(no->filhos[0]);
            if (c != NULL) res.push_back(c); 
        }
        // listaCmd -> cmd listaCmd
        else if (no->filhos.size() == 2) {
            Comando* c = extrai_comando(no->filhos[0]);
            if (c != NULL) res.push_back(c);
            
            vector<Comando *> restante = extrai_lista_comandos(no->filhos[1]);
            res.insert(res.end(), restante.begin(), restante.end());
        }
        return res;
    }

    return res;
}

vector<Comando*> extrai_ifTail(No_arv_parse* no) {
    vector<Comando*> res;
    if (no == nullptr) return res;

    // cmdIfTail -> END
    if (no->filhos[0]->simb == "END") {
        return res; 
    }
    else if (no->filhos[0]->simb == "ELSE")// cmdIfTail -> ELSE bloco END
        return Comando::extrai_lista_comandos(no->filhos[1]);
    else if (no->filhos[0]->simb == "ELSEIF") {// cmdIfTail -> ELSEIF expOr THEN bloco cmdIfTail
        ComandoIf* elseIfCmd = new ComandoIf();
        elseIfCmd->condicao = Expressao::extrai_expressao(no->filhos[1]);
        elseIfCmd->blocoVerdadeiro = Comando::extrai_lista_comandos(no->filhos[3]);
        elseIfCmd->blocoFalso = extrai_ifTail(no->filhos[4]); 
        
        res.push_back(elseIfCmd);
        return res;
    }
    return res;
}

Comando *Comando::extrai_comando(No_arv_parse *no) {
    if (no == NULL) return NULL;

    if (no->simb == "cmd")
        return extrai_comando(no->filhos[0]);

    if (no->simb == "cmdLocal") {
        ComandoLocal *res = new ComandoLocal();
        res->nome = ID::extrai_ID(no->filhos[1])->nome;
        res->tipo = Tipo::extrai_Tipo(no->filhos[2]);
        return res;
    }
    else if (no->simb == "atribuicao") {
        ComandoAtribuicao *res = new ComandoAtribuicao();
        res->esquerda = ID::extrai_ID(no->filhos[0]);
        res->direita = Expressao::extrai_expressao(no->filhos[2]);
        return res;
    }
    else if (no->simb == "retorno") {
        ComandoRetorno *res = new ComandoRetorno();
        res->expressao = Expressao::extrai_expressao(no->filhos[1]);
        return res;
    }
    else if (no->simb == "cmdDo") {
        ComandoDo *res = new ComandoDo();
        res->bloco = Comando::extrai_lista_comandos(no->filhos[1]);
        return res;
    }
    else if (no->simb == "cmdIf") {
        ComandoIf* res = new ComandoIf();
        res->condicao = Expressao::extrai_expressao(no->filhos[1]);
        res->blocoVerdadeiro = Comando::extrai_lista_comandos(no->filhos[3]);
        res->blocoFalso = extrai_ifTail(no->filhos[4]); 
        
        return res;
    }
    else if (no->simb == "cmdWhile") {
        ComandoWhile* res = new ComandoWhile();
        res->condicao = Expressao::extrai_expressao(no->filhos[1]);
        res->bloco = Comando::extrai_lista_comandos(no->filhos[3]);
        return res;
    }
    return NULL;
}

void Comando::debug_com_tab(int tab) {
    tab3(tab);
    cerr << "Comando generico" << endl;
}

Stm* Comando::gerar_IR() {
    return nullptr;
}