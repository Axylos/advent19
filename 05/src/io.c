#include <stdio.h>
#include <stdbool.h>
#include <io.h>
#include <machine.h>

int input;
int output;

int machine_writer(void* data_ptr, int val) {
  printf("got some output: %d\n", val);
  output = val;
  return GO_SIG;
}

int machine_reader(void* data_ptr, enum OpSig* sig) {

  printf("input: %d\n", input);
  return input;
}
