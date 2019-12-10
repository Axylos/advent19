IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
GLOBAL_IDIR=../../include
ODIR=obj
BUILD_DIR=./build
RELEASE_DIR=../../dist

_GLOBAL_OBJ=machine.o
GLOBAL_OBJ=$(patsubst %,$(RELEASE_DIR)/%,$(_GLOBAL_OBJ))

_DEPS=machine.h foo.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=io.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ)) $(GLOBAL_OBJ)

_TEST_OBJ=test.o
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g3 -c -o $@ $< $(CFLAGS)

all: clean run

build: run.o $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

run: build
	./build/run < input.txt

test: $(TEST_OBJ) $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/test $^ $(CFLAGS)
	./build/test < test.txt

check: build
	valgrind --leak-check=yes build/run
	
.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o

release:
	cp $(ODIR)/machine.o $(RELEASE_DIR)
	cp $(IDIR)/machine.h $(IDIR)/io.h $(GLOBAL_IDIR)
