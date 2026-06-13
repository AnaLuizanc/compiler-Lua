CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -Wno-sign-compare
GRAM ?= 1

TARGET := compilador
BUILD_DIR := build
GRAM_DIR := src/src-gram$(GRAM)
GRAM_FILE ?= gramatica-$(GRAM)/gramatica-$(GRAM).site
TABELA_FILE ?= gramatica-$(GRAM)/tabela_lr1.conf

CORE_SRCS := \
	src/sol.cpp \
	src/Arvore.cpp \
	src/Gramatica.cpp \
	src/Parser.cpp \
	src/TabelaLR1.cpp \
	src/debug-util.cpp \
	src/matriz-util.cpp

GRAM_SRCS := $(wildcard $(GRAM_DIR)/*.cpp)
LAB4_SRCS := $(wildcard lab4-frame/*.cpp)
SRCS := $(CORE_SRCS) $(GRAM_SRCS) $(LAB4_SRCS)
OBJS := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

.PHONY: all clean run test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -I$(GRAM_DIR) -Isrc -MMD -MP -c $< -o $@

run: $(TARGET)
	./$(TARGET) $(GRAM_FILE) $(TABELA_FILE)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

test: all
	@echo "\n============================================="
	@echo "        INICIANDO BATERIA DE TESTES        "
	@echo "=============================================\n"
	@for file in ins/*.tokens; do \
		echo "▶ Testando: $$file"; \
		timeout 2s ./compilador gramatica-1/gramatica-1.site gramatica-1/tabela_lr1.conf 10 5 < "$$file" > out.log 2> err.log; \
		STATUS=$$?; \
		if [ $$STATUS -eq 0 ]; then \
			echo "   ✅ [SUCESSO] Valor retornado:"; \
			grep -E "Tamanho total|Variaveis|Resultado final" out.log | sed 's/^/      -> /'; \
		elif [ $$STATUS -eq 124 ]; then \
			echo "   ⚠️ [FALHA] Loop Infinito detectado (Timeout de 2s)"; \
		else \
			echo "   ❌ [FALHA]"; \
			if grep -q "Funcao:" err.log; then \
				sed -n '/Funcao:/,$$p' err.log | sed 's/^/      -> /'; \
			else \
				grep "Erro " err.log | sed 's/^/      -> /' || tail -n 2 err.log | sed 's/^/      -> /'; \
			fi; \
		fi; \
		echo "---------------------------------------------"; \
	done
	@rm -f out.log err.log

test-lab4: all
	@echo "\n============================================="
	@echo "        TESTES ESPECIFICOS DO LAB 4        "
	@echo "=============================================\n"
	@for file in lab4-frame/ins/*.tokens; do \
		echo "▶ Testando Frame de: $$file"; \
		timeout 2s ./compilador $(GRAM_FILE) $(TABELA_FILE) < "$$file" > out.log 2> err.log; \
		STATUS=$$?; \
		if [ $$STATUS -eq 0 ]; then \
			echo "   ✅ [SUCESSO] Alocacao:"; \
			grep -E "Tamanho total|entrada|Memoria|registradores|Maximo|alocadas" out.log | sed 's/^/      -> /'; \
		elif [ $$STATUS -eq 124 ]; then \
			echo "   ⚠️ [FALHA] Timeout (Loop infinito)"; \
		else \
			echo "   ❌ [FALHA] Erro de compilacao/execucao:"; \
			tail -n 3 err.log | sed 's/^/      -> /'; \
		fi; \
		echo "---------------------------------------------"; \
	done
	@rm -f out.log err.log

-include $(DEPS)
