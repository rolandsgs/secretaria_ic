CC = gcc
LIBS = -lGLU -lSOIL -lGL -lglut -lm
MKDIR_P = mkdir -p
OBJ_DIR := obj/
BIN_DIR := bin/

.PHONY: directories
all: directories secretaria

directories: ${OBJ_DIR} ${BIN_DIR}

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

${BIN_DIR}:
	${MKDIR_P} ${BIN_DIR}

secretaria: display
	$(CC) src/main.c obj/display.o $(LIBS) -o bin/secretaria  
	
display: 
	$(CC) -c src/display.c -o obj/display.o
	
