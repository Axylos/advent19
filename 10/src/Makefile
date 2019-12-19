IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
ODIR=obj
BUILD_DIR=./build

_DEPS=
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=run.o 
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJ2=run2.o tree.o
OBJ2=$(patsubst %,$(ODIR)/%,$(_OBJ2))


_TEST_OBJ=test.o
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g3 -o $@ $< $(CFLAGS)

all: clean run

build: $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

build2: two.c
	$(CC) -g3 -o $(BUILD_DIR)/run2 $^ $(CFLAGS)

run: build
	./build/run < input.txt

two: build2
	./build/run2 < input.txt

test: $(TEST_OBJ) $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/test $^ $(CFLAGS)
	./build/test < test.txt

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o
	rm -rf $(BUILD_DIR)/*
