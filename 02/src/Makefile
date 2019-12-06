CC=gcc
IDIR=../include
CFLAGS=-I$(IDIR) -Wall -Werror -std=c99
ODIR=obj

_DEPS=day2.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ=day2.o runner.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

all: clean run

run: $(OBJ)
	$(CC) -g -o $@ $^ $(CFLAGS)
	./run < input.txt

.PHONY: test
.PHONY: clean

clean:
	rm -rf $(ODIR)/*.o *~ core

test: $(OBJ) $(TEST_OBJ)
	$(CC) -o test_runner $^ $(CFLAGS)
	./test_runner
