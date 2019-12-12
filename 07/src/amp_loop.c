#include <amp_loop.h>
#include <stdio.h>
#include <stdlib.h>
#include <machine.h>
#include <string.h>

#define SIZE 10
int machine_reader(void* data_ptr, enum OpSig* sig) {
  struct Executioner* ex = (struct Executioner*)data_ptr;
  if (ex->phases[ex->active_machine] >= 5) {
    int val = ex->phases[ex->active_machine];
    ex->phases[ex->active_machine] = 0;
    *sig = PAUSE_SIG;
    return val;
  } else {
    *sig = GO_SIG;
    return ex->current_val;
  }
}

int machine_writer(void* data_ptr, int val) {
  struct Executioner* ex = (struct Executioner*)data_ptr;
  ex->current_val = val;
  printf("output: %d\n", val);
  return PAUSE_SIG;
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

struct Executioner* init_executioner(int prog[], int prog_size) {
  struct Executioner* ex = malloc(sizeof(struct Executioner));
  ex->active_machine = 0;
  for (int i = 0; i < N_PHASES; i++) {
    int* regs = calloc(prog_size, sizeof(int));
    memcpy(regs, prog, prog_size * sizeof(int));
    struct Machine* m = init_machine(prog, prog_size, ex);
    ex->machines[i] = m;
  }
  return ex;
}

struct Machine* get_active_machine(struct Executioner* ex) {
  if (ex->active_machine >= N_PHASES) {
    puts("true");
    ex->active_machine = 0;
  }
  struct Machine* m = ex->machines[ex->active_machine];

  m->state = GO_SIG;
  return m;
}

void inc_machine(struct Executioner* ex) {
  ex->active_machine++;
}

int compute_val(struct Executioner* ex, int phases[N_PHASES]) {
  memcpy(ex->phases, phases, sizeof(ex->phases));
  enum OpSig sig = GO_SIG;
  while (sig == GO_SIG) {
    printf("%d\n", ex->active_machine);
    sig = run(get_active_machine(ex));
    inc_machine(ex);
  }

  return ex->current_val;
}
