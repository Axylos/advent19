IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
ODIR=obj
BUILD_DIR=./build

_DEPS=op.h machine.h digest.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=machine.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_OBJ=test.o
TEST_OBJ=$(patsubst %,$(ODIR)/%,$(_TEST_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g3 -o $@ $< $(CFLAGS)

all: clean run

build: run.o $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

run: build
	./build/run < input.txt

test: $(TEST_OBJ) $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/test $^ $(CFLAGS)
	./build/test < test.txt

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o
