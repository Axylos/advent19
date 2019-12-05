all: clean build run

clean:
	rm -rf run.o

build: main.c
	gcc -o run.o main.c

run: run.o
	./run.o < input.txt
