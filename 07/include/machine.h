#ifndef MACHINE_H_SEEN
#define MACHINE_H_SEEN

#define OP_LIST_SIZE 50
enum OpSig {
  GO_SIG,
  HALT_SIG,
  PAUSE_SIG
};

int machine_reader(void* data_ptr, enum OpSig* sig);
int machine_writer(void* data_ptr, int val);

struct Machine {
  int ip;
  int* regs;
  void* data_ptr;
  int reg_size;
  enum OpSig state;
};

void print_regs(struct Machine* machine);
struct Machine* init_machine(int* op_list, int list_size,
    void* data_ptr);


//void free_machine(struct Machine* machine);
void output(int val);
int run(struct Machine* machine);

int step(struct Machine* machine);
#endif
