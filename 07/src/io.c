#include <stdio.h>
#include <stdlib.h>
#include <amp_chain.h>

#define SIZE 10

int machine_reader(void* data_ptr, enum OpSig* sig) {
  struct Store* store = (struct Store*)data_ptr;

  long ret = store->send_input ? store->current_val : store->phases[store->amp_n++];
  store->send_input = !store->send_input;
  return ret;
}

int machine_writer(void* data_ptr, long val) {
  struct Store* store = (struct Store*)data_ptr;
  store->current_val = val;

  return 0;
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

