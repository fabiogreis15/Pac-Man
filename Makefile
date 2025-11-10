# Compilador e flags
CC = gcc
CFLAGS = -Wall -Iinclude

# Pastas
SRC_DIR = src
BUILD_DIR = build
CLI_DIR = cli-lib

# Arquivos fonte e objetos
SRC_FILES = $(SRC_DIR)/main.c $(SRC_DIR)/game.c $(SRC_DIR)/map.c $(SRC_DIR)/player.c $(CLI_DIR)/cli.c
OBJ_FILES = $(SRC_FILES:%.c=$(BUILD_DIR)/%.o)

# Nome do executável final
TARGET = $(BUILD_DIR)/pacman

# Regra padrão (quando rodar "make")
all: $(TARGET)

# Como compilar o executável
$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(TARGET)

# Como compilar cada arquivo .c em .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar builds antigos
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Rodar o jogo
run: all
	./$(TARGET)
