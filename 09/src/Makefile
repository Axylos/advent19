IDIR=../include
CC=clang
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
ODIR=obj
BUILD_DIR=./build

_DEPS=
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_OBJ2=run2.o tree.o
OBJ2=$(patsubst %,$(ODIR)/%,$(_OBJ2))

MACH_LIB=../../dist/machine.o
_TEST_OBJ=test.o
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))

all: clean run

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g3 -o $@ $< $(CFLAGS)


build: run.c $(MACH_LIB)
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

build2: two.c
	$(CC) -g3 -o $(BUILD_DIR)/run2 $^ $(CFLAGS)

run: $(ODIR)/run.o
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(MACH_LIB) $(CFLAGS)
	./build/run < input.txt

two: build2
	./build/run2 < input.txt

test: $(ODIR)/test.o $(OBJ) 
	$(CC) -g3 -o $(BUILD_DIR)/test $^ $(MACH_LIB) $(CFLAGS)
	./build/test < test.txt

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o
