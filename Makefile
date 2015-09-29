CC = gcc
LIBS = -lglu32 -lSOIL -lOpenGL32 -lfreeglut

all: secretaria

secretaria: display
	$(CC) src/main.c obj/display.o $(LIBS) -o bin/secretaria  
	
display: 
	$(CC) -c src/display.c -o obj/display.o
	
