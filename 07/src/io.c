#include <stdio.h>
#include <amp_chain.h>
#include <assert.h>
int machine_reader(void* data_ptr) {
  struct Store* store = (struct Store*)data_ptr;
  printf("store: %d %d\n", store->amp_n, store->send_input);

  int ret = store->send_input ? store->current_val : store->phases[store->amp_n++];
  store->send_input = !store->send_input;
  printf("ret: %d\n", ret);
  return ret;
}

void machine_writer(void* data_ptr, int val) {
  struct Store* store = (struct Store*)data_ptr;
  printf("the value is: %d\n", val);
  store->current_val = val;
}
