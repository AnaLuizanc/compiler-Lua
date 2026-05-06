JAVACC := javacc
JAVAC  := javac
JAVA   := java

GRAMMAR := LexicalAnalysis.jj
MAIN    := MyParser

# O parser atual lê este caminho fixo em LexicalAnalysis.jj
INPUT_DIR  := scripts
INPUT_FILE  := $(INPUT_DIR)/compil-lab1-amostra-B-ana-luiza-nobre-cordeiro.lua

# Arquivos gerados pelo JavaCC / Java
GENERATED := $(MAIN).java \
             $(MAIN)TokenManager.java \
             $(MAIN)Constants.java \
             ParseException.java \
             TokenMgrError.java \
             Token.java \
             SimpleCharStream.java

.PHONY: all generate build run clean rebuild

all: run

generate:
	$(JAVACC) $(GRAMMAR)

build: generate
	$(JAVAC) *.java

run: build
	mkdir -p $(INPUT_DIR)
	cp amostra.lua $(INPUT_FILE)
	$(JAVA) $(MAIN)

clean:
	rm -f *.class $(GENERATED) compil-lab1-resposta-C-ana-luiza-nobre-cordeiro
	rm -rf $(INPUT_DIR)

rebuild: clean run
