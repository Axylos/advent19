#include <machine.h>
#include <stdio.h>
#include <string.h>
#include <amp_chain.h>
#include <stdlib.h>

#define N_PHASES 5
#define SIZE 10

void swap(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

void tune_machine(struct Store* store, int phases[N_PHASES]) {
  store->amp_n = 0;
  store->send_input = false;
  store->phases = phases;
  store->current_val = 0;
}

void reset_machine(struct Machine* machine, long program[], int prog_size) {
  memcpy(machine->regs, program, prog_size * sizeof(long));
  machine->ip = 0;
  machine->state = GO;
  struct Store* store = (struct Store*)machine->data_ptr;
  store->send_input = false;
}


long compute_output(int phases[N_PHASES], long program[], int prog_size, struct Machine* machine) {
  struct Store* store = (struct Store*)machine->data_ptr;
  tune_machine(store, phases);
  for (int i = 0; i < N_PHASES; i++) {
    reset_machine(machine, program, prog_size);
    run(machine);
  }
  return store->current_val;
}

long find_max_signal(int phases[N_PHASES], int l, int r, long list[], int size, int* max) {
  struct Store* store = malloc(sizeof(struct Store));
  store->phases = phases;
  store->current_val = 0;
  store->amp_n = 0;
  store->send_input = true;

  struct Machine* machine = init_machine(list, size, store);
  if (l == r) {
    memcpy(machine->regs, list, size * sizeof(long));
    
    long signal = compute_output(phases, list, size, machine);
    if (signal > *max) {
      *max = signal;
    }
  } else {
    for (int i = l; i <= r; i++) {
      swap((phases + l), (phases + i));
      find_max_signal(phases, l + 1, r, list, size, max);
      swap((phases+ l), (phases + i));
    }
  }
  return *max;
}

