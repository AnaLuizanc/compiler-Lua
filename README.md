# compiler-Lua

Compilador para a linguagem Lua 5.1 desenvolvido na disciplina de **Compiladores** ministrada por Alberto Alexandre Miranda.

## FASE 1 — Análise Léxica: Implementação de um analisador léxico para Lua usando JavaCC.

Analisador léxico para Lua implementado com **JavaCC**. Lê um script `.lua` e gera um arquivo de saída com os tokens identificados no formato `CLASSE valor`.

**Tokens reconhecidos:** palavras-chave, identificadores, números (com notação científica), strings, operadores, delimitadores e símbolos especiais. Comentários (`--`) e espaços em branco são ignorados.

### Como executar

```bash
# A partir do diretório lab1-lexicalAnalysis/
javacc LexicalAnalysis.jj
javac *.java
java MyParser file-name.lua > saida-amostra-lab1.tokens
```

A saída do analisador será gravada em `output.txt`.

Para atender os requisitos de estrutura do projeto na próxima fase, deve rodar o comando abaixo:
```bash
printf '$ $\n' >> output.txt
```
O comando acima adiciona uma linha contendo dois símbolos $, separada por espaço.
Ela é usada como marcação final no arquivo de saída, conforme o formato exigido pela próxima fase do projeto.

---

## FASE 2 — Construção da Gramática: parser LR(1) para um subconjunto de Lua 5.1

Nesta etapa foi construída a gramática da linguagem e a tabela LR(1) utilizada pelo parser sintático. O objetivo é reconhecer uma versão intermediária de Lua 5.1 com comandos, expressões, chamadas de função e construtores de tabela.

### Arquivos principais

- `lab2-buildingGrammar/parserLR/gramatica.conf` — arquivo com as produções da gramática.
- `lab2-buildingGrammar/parserLR/tabela_lr1.conf` — tabela LR(1) linearizada usada pelo parser.
- `lab2-buildingGrammar/parserLR/src/` — implementação do parser em C++.
- `lab2-buildingGrammar/lineariza-tabela.js` — script auxiliar para linearizar a tabela a partir da visualização HTML.

### O que a gramática cobre

A gramática inclui construções como:

- comandos de controle: `if`, `elseif`, `else`, `while`
- declarações: `local`, `return`, `function`
- expressões aritméticas, relacionais e lógicas
- chamadas de função
- acesso por campo e índice
- construtores de tabela com `{ ... }`

### Como executar

A partir do diretório `lab2-buildingGrammar/`:

```bash
g++ src/*.cpp -o bin/parser
bin/parser < file-output.txt 2> resposta.txt 
```

A saída é redirecionada para `resposta.txt`, que pode conter mensagens do parser ou o resultado esperado pela disciplina.

## FASE 3 — Análise Semântica: contrução do Interpretador e Avaliador

Nesta etapa, o compilador passa a interpretar e dar significado à Árvore de Sintaxe Abstrata (AST) gerada pelo parser, transformando-se num motor de execução capaz de calcular resultados reais em C++11.

### O que foi implementado
- **Tipagem Estrita e Coerção**: Validação de tipos em tempo de compilação para INT, FLOAT e BOOL, incluindo coerção automática de INT para FLOAT em operações matemáticas mistas.
- **Memória e Escopos Dinâmicos**: Suporte estruturado para variáveis locais e parâmetros de função, garantindo que o escopo (shadowing) funcione perfeitamente em blocos aninhados.
- **Controle de Fluxo Funcional**: Avaliação dinâmica para ramificações condicionais (if, elseif, else) e laços de repetição (while).
- **Segurança de Execução**: Travas contra divisões por zero e verificação de variáveis não inicializadas (com fallback seguro para evitar Segmentation Fault).
- **Formatação de Saída**: O último valor retornado ou atribuído é impresso com formatação rigorosa (FLOAT com 2 casas decimais, BOOL como true/false).

### Como executar
A partir do diretório do Lab 3, compile o projeto utilizando o Makefile:

````bash 
make clean
make
````

O analisador recebe os parâmetros de entrada da função simulada diretamente via linha de comando, logo após os arquivos de configuração do parser.

````bash
# Exemplo passando os parâmetros '10' e '5' para o script
./compilador gramatica-1/gramatica-1.site gramatica-1/tabela_lr1.conf 10 5 < ins/arquivo_de_teste.tokens
````

### Como executar (Bateria de Testes Automatizados)
Para facilitar a validação e garantir que a AST é interpretada corretamente sem poluir o terminal, foi criado um script integrado no Makefile.

Ele processa todos os ficheiros de teste na pasta de entradas e exibe apenas o valor retornado ou os erros semânticos encontrados. Ele inclui um mecanismo de timeout (2s) para identificar e interromper testes com Loops Infinitos.

````bash
make test
````

## Fase 4: Geração de Frame e Alocação de Memória

O objetivo desta etapa é construir a infraestrutura da arquitetura de ativação de funções, realizando o cálculo do Frame de Execução e planeando a alocação de variáveis na memória (Frame) ou em pseudo-registradores, a partir da Árvore de Sintaxe Abstrata (AST).

*Nota: Conforme os requisitos desta fase, a Análise Semântica (Fase 3) foi desativada na rotina de execução principal (`sol.cpp`) para isolar os testes e o funcionamento do cálculo estrutural de memória.*

### O que foi implementado

Para suportar o planeamento de memória e a passagem de parâmetros, as seguintes extensões foram implementadas na infraestrutura do compilador:
- **Classe `FrameFuncao`**: Criada a classe responsável por analisar a AST da função e calcular o seu escopo de memória. Ela determina os seguintes valores estruturais:
    * `tamanho_frame`: Total de bytes alocados (mínimo de 40 bytes para controlo de contexto + 8 bytes por variável que vai para a memória).
    * `n_param_entrada`: Quantidade de parâmetros recebidos na declaração da função.
    * `n_maximo_param_saida`: O maior número de argumentos enviados numa chamada de função interna.
    * `n_pseudo_registradores`: Total de variáveis internas otimizadas que não escapam para a memória.
    * `n_variaveis_no_frame`: Total de variáveis locais que sofrem *escape* e precisam de ser guardadas na RAM.

- **Escape Analysis e Mapeamento (`FrameAcesso`)**: O nó que representa a variável na AST (`Fator`) passou a contar com uma propriedade polimórfica `FrameAcesso`, que é atribuída seguindo uma rigorosa análise de escape:
    * **`FrameAcessoNoFrame`:** Variáveis que são passadas como parâmetros para outras funções "escapam" do escopo estrito local. Estas são alocadas na memória em posições negativas (ex: `FP-40`, `FP-48`), em blocos de 8 bytes.
    * **`FrameAcessoTemp`:** Variáveis que não "escapam" são alocadas em pseudo-registradores, recebendo IDs numéricos sequenciais (a partir de 1).
    * **Garantia de Ordem:** O código rastreia as variáveis (via `std::vector`) pela exata ordem de declaração no código fonte, garantindo que a numeração dos pseudo-registradores respeita a ordem de aparecimento ditada pelos requisitos do projeto.
    * Os parâmetros de entrada assumem posições no frame anterior (ex: `FP+8`, `FP+16`). Todas as referências subsequentes a uma variável partilham o mesmo apontador em memória.

---

### Como executar
A partir do diretório do Lab 3, compile o projeto utilizando o Makefile:

```bash
# Limpa binários e objetos de compilações anteriores
make clean

# Compila o projeto e gera o executável 'compilador'
make test-lab4 

# OU
./compilador gramatica-1/gramatica-1.site gramatica-1/tabela_lr1.conf < lab4-frame/ins/arquivo.tokens