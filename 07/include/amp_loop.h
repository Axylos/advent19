#ifndef FILE_AMP_LOOP
#define FILE_AMP_LOOP

#define N_PHASES 5

struct Executioner {
  int current_val;
  int active_machine;
  struct Machine* machines[N_PHASES];
  int phases[N_PHASES];
};
int* ingest(int* size);

struct Executioner* init_executioner(int prog[], int prog_size);
int compute_val(struct Executioner* ex, int phases[N_PHASES]);

#endif
