#include <stdio.h>
#include <amp_chain.h>
int machine_reader(void* data_ptr) {
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
