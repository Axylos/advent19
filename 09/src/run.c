#include <stdio.h>
#include <stdlib.h>
#include <op.h>
#include <machine.h>
#include <assert.h>
#include <string.h>
#define SIZE 50

int toggle = 0;

int machine_reader(void* data_ptr, enum OpSig* sig) {
  if (toggle == 0) {
    return 1;
  } else {
    return 2;
  }
}

int machine_writer(void* data_ptr, long val) {
  long* output = (long*)data_ptr;
  *output = val;

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
   for (int i = 0; i < size; i++) {
    dest[i] = src[i];
  }
 
}

void test_eq(long* a, long* b, int size) {
  for (int i = 0; i < size; i++) {
    if (a[i] != b[i]) {
      printf("bad vals: %ld %ld at idx: %d\n", a[i], b[i], i);
      assert(0);
    }
  }
}

int main(int argc, char* argv[]) {
  int prog_size = 0;
  long* input = ingest(&prog_size);
  long* prog = calloc(prog_size, sizeof(long));
  long* prog2 = calloc(prog_size, sizeof(long));
  reset_prog(prog, input, prog_size);
  reset_prog(prog2, input, prog_size);

  test_eq(input, prog, prog_size);

  long output = -1;
  struct Machine* m = init_machine(prog, prog_size, &output);
  run(m);
  assert(output == 2453265701);
  printf("Output from part I: %ld\n", output);
  free(m);

  output = -1;
  toggle = 1;
  test_eq(input, prog2, prog_size);
  struct Machine* m2 = init_machine(prog2, prog_size, &output);
  run(m2);
  printf("output from part II: %ld\n", output);
  assert(output == 80805);
  return 0;
}
