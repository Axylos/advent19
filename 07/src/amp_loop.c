#include <amp_loop.h>
#include <stdio.h>
#include <stdlib.h>
#include <machine.h>
#include <string.h>

#define SIZE 10
int machine_reader(void* data_ptr, enum OpSig* sig) {
  struct Executioner* ex = (struct Executioner*)data_ptr;
  if (ex->phases[ex->active_machine] >= 5) {
    long val = ex->phases[ex->active_machine];
    ex->phases[ex->active_machine] = 0;
    *sig = PAUSE;
    return val;
  } else {
    *sig = GO;
    return ex->current_val;
  }
}

int machine_writer(void* data_ptr, long val) {
  struct Executioner* ex = (struct Executioner*)data_ptr;
  ex->current_val = val;
  return PAUSE;
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

struct Executioner* init_executioner(long prog[], int prog_size) {
  struct Executioner* ex = malloc(sizeof(struct Executioner));
  ex->active_machine = 0;
  for (int i = 0; i < N_PHASES; i++) {
    long* regs = calloc(prog_size, sizeof(long));
    memcpy(regs, prog, prog_size * sizeof(long));
    struct Machine* m = init_machine(regs, prog_size, ex);
    ex->machines[i] = m;
  }
  return ex;
}

struct Machine* get_active_machine(struct Executioner* ex) {
  if (ex->active_machine >= N_PHASES) {
    ex->active_machine = 0;
  }
  struct Machine* m = ex->machines[ex->active_machine];

  m->state = GO;
  return m;
}

void inc_machine(struct Executioner* ex) {
  ex->active_machine++;
}

int compute_val(struct Executioner* ex, int phases[N_PHASES]) {
  memcpy(ex->phases, phases, sizeof(ex->phases));
  enum OpSig sig = GO;
  struct Machine* m;
  while (sig != HALT) {
    m = get_active_machine(ex);
    run(get_active_machine(ex));
    sig = m->state;
    inc_machine(ex);
  }

  return ex->current_val;
}

void swap(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}


int find_max_thrust(int phases[N_PHASES], int l, int r, long prog[], int prog_size, int* max) {

  if (l == r) {
    struct Executioner* ex = init_executioner(prog, prog_size);
    int signal = compute_val(ex, phases);

    if (signal > *max) {
      *max = signal;
    }
  } else {
    for (int i = l; i <= r; i++) {
      swap((phases + l), (phases + i));
      find_max_thrust(phases, l + 1, r, prog, prog_size, max);
      swap((phases+ l), (phases + i));
    }
  }
  return *max;
}

