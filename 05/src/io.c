#include <stdio.h>
#include <stdbool.h>

bool toggle = true;
void machine_writer(void* data_ptr, int val) {
  printf("got some output: %d\n", val);
}

int machine_reader(void* data_ptr) {
  int val = toggle ? 1 : 5;
  toggle = !toggle;

  return val;
}
