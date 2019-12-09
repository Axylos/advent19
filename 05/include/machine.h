#ifndef MACHINE_H_SEEN
#define MACHINE_H_SEEN

#define OP_LIST_SIZE 50

#include <machine.h>

struct Machine {
  int ip;
  int* regs;
  int(*get_input)();
  void(*put_output)(int val);
};

struct Machine* init_machine(int* op_list,
    int(*input_fn)(), void(*output_fn)(int val));

int input_one();
void output(int val);
int run(struct Machine* machine);
struct Machine* init_machine(int* op_list,
    int(*input_fn)(), void(*output_fn)(int val));

int step(struct Machine* machine);
#endif
