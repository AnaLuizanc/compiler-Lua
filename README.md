# compiler-Lua

Compilador para a linguagem Lua 5.1 desenvolvido na disciplina de **Compiladores** ministrada por Alberto Alexandre Miranda.

## FASE 1 — Análise Léxica: Implementação de um analisador léxico para Lua usando JavaCC.

Analisador léxico para Lua implementado com **JavaCC**. Lê um script `.lua` e gera um arquivo de saída com os tokens identificados no formato `CLASSE valor`.

**Tokens reconhecidos:** palavras-chave, identificadores, números (com notação científica), strings, operadores, delimitadores e símbolos especiais. Comentários (`--`) e espaços em branco são ignorados.

### Como executar

```bash
# A partir do diretório lexicalAnalysis/
javacc LexicalAnalysis.jj
javac *.java
java MyParser
```

A saída é gravada em `compil-lab1-resposta-C-ana-luiza-nobre-cordeiro`.
