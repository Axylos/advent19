#ifndef MACHINE_H_SEEN
#define MACHINE_H_SEEN

#define OP_LIST_SIZE 50

struct Machine {
  int ip;
  int* regs;
  int(*get_input)();
  void(*put_output)(int val);
  int reg_size;
};

struct Machine* init_machine(int* op_list, int list_size,
    int(*input_fn)(), void(*output_fn)(int val));

int input_one();
void output(int val);
int run(struct Machine* machine);

int step(struct Machine* machine);
#endif
