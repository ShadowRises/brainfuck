CC 	= gcc
CFLAGS 	= -std=c99 -Wall -pedantic
LDFLAGS =
OUTPUT_OPTION = -MMD -MP -o $@
TARGET 	= brainfuck

SRC_DIR = src
OBJ_DIR = obj
SRC 	= $(wildcard $(SRC_DIR)/*.c)
OBJ 	= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC:.c=.o))
DEP	= $(OBJ:.o=.d)

.PHONY: all help clean
all: $(OBJ_DIR) $(OBJ) $(TARGET)

help:
	-@echo "Targets:"
	-@printf "\tall (default)         Run 'brainfuck' rule\n"
	-@printf "\tbrainfuck             Compile 'brainfuck'\n"
	-@printf "\tclean                 Remove all build artifacts\n"

clean:
	rm -rf $(TARGET) $(OBJ_DIR)/


-include ${DEP}

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(OUTPUT_OPTION)
