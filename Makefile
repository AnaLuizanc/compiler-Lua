JAVACC := javacc
JAVAC  := javac
JAVA   := java

GRAMMAR := LexicalAnalysis.jj
MAIN    := MyParser

# Arquivo de entrada padrão usado no README
INPUT_FILE  := amostra.lua \
			   amostra-correcao2.lua
OUTPUT_TOKENS := saida-amostra-lab1.tokens \
				 saida-amostra-lab2.tokens

# Arquivos gerados pelo JavaCC / Java
GENERATED := $(MAIN).java \
             $(MAIN)TokenManager.java \
             $(MAIN)Constants.java \
             ParseException.java \
             TokenMgrError.java \Z
             Token.java \
             SimpleCharStream.java

.PHONY: all generate build run postprocess clean rebuild

all: run

generate:
	$(JAVACC) $(GRAMMAR)

build: generate
	$(JAVAC) *.java

run: build
	$(JAVA) $(MAIN) $(INPUT_FILE) > $(OUTPUT_TOKENS)

postprocess:
	printf '$ $\n' >> $(OUTPUT_TOKENS)

clean:
	rm -f *.class $(GENERATED) $(OUTPUT_TOKENS)

rebuild: clean run postprocess