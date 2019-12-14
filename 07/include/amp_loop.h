#ifndef FILE_AMP_LOOP
#define FILE_AMP_LOOP

#define N_PHASES 5

struct Executioner {
  int current_val;
  int active_machine;
  struct Machine* machines[N_PHASES];
  int phases[N_PHASES];
};
long* ingest(int* size);
int find_max_thrust(int phases[N_PHASES], int l, int r, long list[], int size, int* max);
struct Executioner* init_executioner(long prog[], int prog_size);
int compute_val(struct Executioner* ex, int phases[N_PHASES]);

#endif
