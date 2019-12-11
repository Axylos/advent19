#ifndef MACHINE_H_SEEN
#define MACHINE_H_SEEN

#include <io.h>

#define OP_LIST_SIZE 50

struct Machine {
  int ip;
  int* regs;
  void* data_ptr;
  int reg_size;
};
void print_regs(struct Machine* m);
struct Machine* init_machine(int* op_list, int list_size,
    void* data_ptr);


void free_machine(struct Machine* machine);
void output(int val);
int run(struct Machine* machine);

int step(struct Machine* machine);
#endif
