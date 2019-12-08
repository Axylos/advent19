IDIR=../include
CC=gcc
CFLAGS=-I$(IDIR) -std=c11 -Werror -Wall
ODIR=obj
BUILD_DIR=./build

_DEPS=
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=point.o op.o walk.o runner.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g3 -o $@ $< $(CFLAGS)

all: clean run

build: $(OBJ)
	$(CC) -g3 -o $(BUILD_DIR)/run $^ $(CFLAGS)

run: build
	./build/run < input.txt

test: build
	./build/run < test.txt

.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o
