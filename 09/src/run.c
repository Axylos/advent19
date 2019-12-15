#include <stdio.h>
#include <stdlib.h>
#include <op.h>
#include <machine.h>
#include <assert.h>
#include <string.h>
#define SIZE 50

int toggle = 0;

int machine_reader(void* data_ptr, enum OpSig* sig) {
  printf("toggle: %d\n", toggle);
  if (toggle == 0) {
    return 1;
  } else {
    return 2;
  }
}

int machine_writer(void* data_ptr, long val) {
  long* output = (long*)data_ptr;
  *output = val;
  printf("got some output: %ld\n", val);

  return GO;
}


long* ingest(int* size) {
  long* list = calloc(SIZE, sizeof(long));
  int capacity = SIZE;
  int _size = 0;
  int i;
  while(scanf("%d,?", &i) != EOF) {
    if (_size == capacity) {
      capacity *= 2;
      list = realloc(list, capacity * sizeof(long));
    }


    list[_size++] = i;
  }

  *size = _size;
  return list;
}

void reset_prog(long* dest, long* src, int size) {
  printf("size: %d\n", size);
   for (int i = 0; i < size; i++) {
    dest[i] = src[i];
  }
 
}

int main(int argc, char* argv[]) {
  int prog_size = 0;
  long* input = ingest(&prog_size);
  long* prog = calloc(prog_size, sizeof(long));
  reset_prog(prog, input, prog_size);

  long output = -1;
  //struct Machine* m = init_machine(prog, prog_size, &output);
  //run(m);
  //assert(output == 2453265701);

  reset_prog(prog, input, prog_size);
  output = -1;
  toggle = 1;
  struct Machine* m2 = init_machine(prog, prog_size, &output);
  run(m2);
  return 0;
}
