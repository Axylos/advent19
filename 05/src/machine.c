#include <op.h>
#include <machine.h>
#include <stdlib.h>

struct Machine* init_machine(int* op_list,
    int(*input_fn)(), void(*output_fn)(int val)) {
  struct Machine* machine = malloc(sizeof(struct Machine));
  machine->idx = 0;
  machine->regs = op_list;
  machine->get_input = input_fn;
  machine->put_output = output_fn;

  return machine;
}

int step(struct Machine* machine) {
  return machine->regs[machine->idx++];
}

struct Op* parse_op(struct Machine* machine, int op_code) {
  union Instruction* instruction = malloc(sizeof(union Instruction));
  struct Op* op = malloc(sizeof(struct Op));
  switch(op_code) {
    case ADD: ;
      struct AddOp* add_op = malloc(sizeof(struct AddOp));
      add_op->a = step(machine);
      add_op->b = step(machine);
      add_op->targ = step(machine);
      instruction->add_op = add_op;
      op->op_type = ADD;
      break;
    case INPUT: ;
      struct InputOp* input_op = malloc(sizeof(struct InputOp));
      input_op->targ = step(machine);
      input_op->val = machine->get_input();
      instruction->input_op = input_op;
      op->op_type = INPUT;
      break;
    case OUTPUT: ;
      struct OutputOp* output_op = malloc(sizeof(struct OutputOp));
      output_op->val = step(machine);
      instruction->output_op = output_op;
      op->op_type = OUTPUT;
      break;
  }

  op->instruction = instruction;
  return op;
}

void eval(struct Machine* machine, struct Op* op) {
  union Instruction inst = *(op->instruction);
  switch(op->op_type) {
    case INPUT: ;
      machine->regs[inst.input_op->targ] = inst.input_op->val;
      break;
    case OUTPUT: ;
      int val = machine->regs[inst.output_op->val];
      machine->put_output(val);
      break;
  }
}

int run(struct Machine* machine) {
  int op_code = -1;
  while(op_code != HALT) {
    int op_code = step(machine);
    if (op_code == HALT) {
      return 0;
    }
    struct Op* op = parse_op(machine, op_code);
    eval(machine, op);
  }

  return 0;
}
