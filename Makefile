CXX = g++
CXXFLAGS = -std=c++11 -Wall

JAVACC = javacc
JAVA = java
JAVAC = javac

LEXER = lab1-lexicalAnalysis/LexicalAnalysis.jj

PARSER_BIN = lab2-buildingGrammar/bin/parser

INS_DIR = lab3-semanticAnalysis/ins

LUA_FILES = $(wildcard $(INS_DIR)/*.lua)

TOKEN_FILES = $(LUA_FILES:.lua=.tokens)

OUT_FILES = $(LUA_FILES:.lua=.out)

CPP_SRCS = $(wildcard lab2-buildingGrammar/src/*.cpp)

.PHONY: all lexer java parser tokens semantic clean

all: tokens semantic

# ==================================================
# FASE 1 - ANALISE LEXICA
# ==================================================

lexer:
	$(JAVACC) $(LEXER)

java: lexer
	$(JAVAC) *.java

tokens: java $(TOKEN_FILES)

%.tokens: %.lua
	@echo "Gerando tokens para $<"
	$(JAVA) MyParser $< > $@
	printf '$$ $$ \n' >> $@

# ==================================================
# FASE 2/3 - PARSER + SEMANTICA
# ==================================================

parser:
	@mkdir -p lab2-buildingGrammar/bin
	$(CXX) $(CXXFLAGS) $(CPP_SRCS) -o $(PARSER_BIN)

semantic: parser $(OUT_FILES)

%.out: %.tokens
	@echo "Executando parser para $<"
	cd lab2-buildingGrammar && ./bin/parser < ../$< 2> ../$@

# ==================================================
# LIMPEZA
# ==================================================

clean:
	rm -f *.java
	rm -f *.class
	rm -f $(TOKEN_FILES)
	rm -f $(OUT_FILES)
	rm -f $(PARSER_BIN)