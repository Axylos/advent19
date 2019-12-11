#ifndef FILE_AMP_CHAIN_H_SEEN
#define FILE_AMP_CHAIN_H_SEEN

#include <stdbool.h>
#include <machine.h>
#define N_PHASES 5
struct Store {
  int* phases;
  int current_val;
  int amp_n;
  bool send_input;
};

int compute_output(int phases[N_PHASES], int program[], int prog_size, struct Machine* machine);
int find_max_signal(int phases[N_PHASES], int l, int r, int list[], int size, int* max);

#endif
