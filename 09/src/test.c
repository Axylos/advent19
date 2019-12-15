#include <stdio.h>
#include <string.h>
#include <machine.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int machine_reader(void* data_ptr, enum OpSig* sig) {
  return 1;
}

int machine_writer(void* data_ptr, long val) {
  long* output = (long*)data_ptr;
  *output = val;
  printf("%ld", val);

  return GO;
}

void copy_test() {
  long val = -1;
  long data[] = { 109,1,204,-1,1001,100,1,100,1008,100,16,101,1006,101,0,99 };
  int prog_size = sizeof(data) / sizeof(long);
  long* prog = calloc(prog_size, sizeof(long));
  for (int i = 0; i < prog_size; i++) {
    prog[i] = data[i];
  }

  struct Machine* m = init_machine(prog, prog_size, &val);
  printf("copy\n");
  run(m);
}

void big_int_test() {
  long val = -1;
  long data[] = { 1102,34915192,34915192,7,4,7,99,0 };
  int prog_size = sizeof(data) / sizeof(long);
  long* prog = calloc(prog_size, sizeof(long));
  for (int i = 0; i < prog_size; i++) {
    prog[i] = data[i];
  }

  struct Machine* m = init_machine(prog, prog_size, &val);
  run(m);
  assert(val > 999999999999999);
  assert(val < 10000000000000000);
}

void mid_num_test() {
  long val = -1;
  long data[] = { 104,1125899906842624,99 };
  int prog_size = sizeof(data) / sizeof(long);
  long* prog = calloc(prog_size, sizeof(long));
  for (int i = 0; i < prog_size; i++) {
    prog[i] = data[i];
  }

  struct Machine* m = init_machine(prog, prog_size, &val);
  run(m);
  printf("val: %ld\n", val);
  assert(val == 1125899906842624);
}

int main(int argc, char* argv[]) {
  copy_test();
  //big_int_test();
  //mid_num_test();
  char str[] = "1125899906842624";
  long foo = 0;
  sscanf(str, "%ld", &foo);
  puts("tests passing");
  return 0;
}
