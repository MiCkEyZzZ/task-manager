# Установки компилятора и флагов
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./includes

# Каталоги
SRC_DIR = src
OBJ_DIR = obj

# Источники и заголовочные файлы
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/task_operations.c $(SRC_DIR)/file_operations.c $(SRC_DIR)/user_input.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Целевой файл
OUT = main

# Основная цель для сборки
all: $(OUT)

# Сборка исполняемого файла
$(OUT): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# Правило для компиляции каждого .c файла в .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка собранных файлов
clean:
	rm -rf $(OBJ_DIR) $(OUT)
