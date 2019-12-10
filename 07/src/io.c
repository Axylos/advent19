#include <stdio.h>
int machine_reader(void* data_ptr) {
  int* ctr = (int*)data_ptr;
  printf("data: %d\n", *ctr);
  *ctr += 1;
  puts("reader");
  return 0;
}

int machine_writer(void* data_ptr, int val) {
  return 1;
}
