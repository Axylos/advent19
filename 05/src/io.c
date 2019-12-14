#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <machine.h>

int input;
int output;

int machine_writer(void* data_ptr, long val) {
  printf("got some output: %ld\n", val);
  output = val;
  return GO;
}

int machine_reader(void* data_ptr, enum OpSig* sig) {

  printf("input: %d\n", input);
  return input;
}
