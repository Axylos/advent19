#ifndef MACHINE_H_SEEN
#define MACHINE_H_SEEN

#include <io.h>
#include <op.h>

#define OP_LIST_SIZE 50

int machine_reader(void* data_ptr, enum OpSig* sig);
int machine_writer(void* data_ptr, long val);

struct Machine {
  int ip;
  long* regs;
  void* data_ptr;
  int reg_size;
  enum OpSig state;
  long rel_base;
};

void print_regs(struct Machine* machine);
struct Machine* init_machine(long* op_list, int list_size,
    void* data_ptr);



//void free_machine(struct Machine* machine);
int run(struct Machine* machine);

long step(struct Machine* machine);
#endif
