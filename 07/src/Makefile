IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
GLOBAL_IDIR=../../include
ODIR=obj
BUILD_DIR=./build
RELEASE_DIR=../../dist

_GLOBAL_OBJ=machine.o
GLOBAL_OBJ=$(patsubst %,$(RELEASE_DIR)/%,$(_GLOBAL_OBJ))

_DEPS=machine.h foo.h amp_chain.h amp_loop.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ)) $(GLOBAL_OBJ)

_TEST_OBJ=test.o
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))

MACHINE_SRC=../../07/src/machine.c

all: clean run
$(ODIR)/machine.o: 
	$(CC) -g3 -c -o $(ODIR)/machine.o ../../05/src/machine.c -I../../07/include/

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -g3 -c -o $@ $< $(CFLAGS)


build: $(ODIR)/run.o $(OBJ) $(ODIR)/amp_chain.o $(ODIR)/io.o
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

run: build
	./build/run < input.txt

test_build: $(ODIR)/test.o $(ODIR)/amp_chain.o $(ODIR)/machine.o $(ODIR)/io.o
	$(CC) -g3 -o $(BUILD_DIR)/test $^ $(CFLAGS)

test: test_build
	./build/test

check: build
	valgrind --leak-check=yes build/run
	
.PHONY: clean

build2: $(ODIR)/two.o $(OBJ) $(ODIR)/amp_loop.o
	$(CC) -g3 -o $(BUILD_DIR)/two $^ $(CFLAGS)

two: build2
	./build/two < input.txt

clean:
	rm -rf $(ODIR)/*.o

release:
	cp $(ODIR)/machine.o $(RELEASE_DIR)
	cp $(IDIR)/machine.h $(IDIR)/io.h $(GLOBAL_IDIR)
