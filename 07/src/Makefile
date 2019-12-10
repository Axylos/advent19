IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
GLOBAL_IDIR=../../include
ODIR=obj
BUILD_DIR=./build
RELEASE_DIR=../../dist

_DEPS=io.h op.h machine.h digest.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=io.o machine.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_OBJ=test.o
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g3 -o $@ $< $(CFLAGS)

all: clean run

build: run.o $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

run: build
	./build/run

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
