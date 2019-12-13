#include <stdio.h>
#include <stdlib.h>
#include <amp_chain.h>

#define SIZE 10

int machine_reader(void* data_ptr, enum OpSig* sig) {
  struct Store* store = (struct Store*)data_ptr;

  int ret = store->send_input ? store->current_val : store->phases[store->amp_n++];
  store->send_input = !store->send_input;
  return ret;
}

int machine_writer(void* data_ptr, int val) {
  struct Store* store = (struct Store*)data_ptr;
  store->current_val = val;

  return 0;
}

int* ingest(int* size) {
  int* list = calloc(SIZE, sizeof(int));
  int capacity = SIZE;
  int _size = 0;
  int i;
  while(scanf("%d,?", &i) != EOF) {
    if (_size == capacity) {
      capacity *= 2;
      list = realloc(list, capacity * sizeof(int));
    }


    list[_size++] = i;
  }

  *size = _size;
  return list;
}

