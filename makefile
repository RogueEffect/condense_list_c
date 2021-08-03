CC = gcc
FLAGS = -g -Wall -std=c99
FILES = main.c
EXE = condense

all: main.c
	$(CC) $(FLAGS) $(FILES) -o $(EXE)
