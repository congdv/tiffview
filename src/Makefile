CC = gcc -Wall -Wextra -pedantic 
CPP = g++ -Wall -Wextra 
LIBS = -lSDL -ltiff 
OPENCV = -ltiff `pkg-config --cflags --libs opencv`
FLAGS = -I/usr/local/include/opencv -I/usr/local/include
all: sdlviewer.c tiffreader.c
	$(CC) sdlviewer.c tiffreader.c -o viewer $(LIBS)
test: test_matrix.h sdlviewer.h
	$(CC)test_matrix.c sdlviewer.c -o test $(OPENCV) $(FLAGS)

