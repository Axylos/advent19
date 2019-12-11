#include <assert.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <machine.h>
#include <string.h>
#include <amp_chain.h>

void test_case() {
  int phases[] = { 4,3,2,1,0 };
  //int phase_size = sizeof(phases) / sizeof(int);

  int prog[] = { 3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0 };

  int prog_size = sizeof(prog) / sizeof(int);
  printf("prog size: %d\n", prog_size);
  int other_prog[prog_size];
  for (int i = 0; i < prog_size; i++) {
    other_prog[i] = prog[i];
  }


  struct Store* store = malloc(sizeof(struct Store));
  store->phases = phases;
  store->current_val = 0;
  store->amp_n = 0;
  store->send_input = true;

  struct Machine* machine = init_machine((int*)other_prog, prog_size, store);
  int sig = compute_output(phases, prog, prog_size, machine);

  assert(sig == 43210);
}

void test_find_max() {
  int phases[] = { 4,3,2,1,0 };
  //int phase_size = sizeof(phases) / sizeof(int);

  int prog[] = { 3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0 };

  int prog_size = sizeof(prog) / sizeof(int);

  int max = -1;
  int i = find_max_signal(phases, 0, 4, prog, prog_size, &max); 
  assert(i == 43210);
}
int main(int argc, char* argv[]) {
  test_case();
  test_find_max();
  return 0;
}
