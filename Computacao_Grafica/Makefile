CXX = g++
CXXFLAGS = -Wall -Wextra -g3
LDFLAGS = -lglut -lGL -lGLU -lm
OUTPUT_DIR = output

# Arquivos fonte e executáveis
SOURCES = $(wildcard *.cpp)
EXECUTABLES = $(patsubst %.cpp,$(OUTPUT_DIR)/%,$(SOURCES))

# Alvo padrão
all: $(OUTPUT_DIR) $(EXECUTABLES)

# Criar diretório output se não existir
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Regra para compilar cada arquivo
$(OUTPUT_DIR)/%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

# Limpar arquivos compilados
clean:
	rm -rf $(OUTPUT_DIR)/*

# Listar todos os arquivos
list:
	@echo "Arquivos disponíveis:"
	@ls -la *.cpp

.PHONY: all clean list
