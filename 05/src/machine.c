#include <op.h>
#include <machine.h>
#include <stdlib.h>
#include <assert.h>

struct Machine* init_machine(int* op_list,
  int(*input_fn)(), void(*output_fn)(int val)) {
  struct Machine* machine = malloc(sizeof(struct Machine));
  machine->ip = 0;
  machine->regs = op_list;
  machine->get_input = input_fn;
  machine->put_output = output_fn;

  return machine;
}

int step(struct Machine* machine) {
  return machine->regs[machine->ip++];
}

void exec_input(struct Machine* machine, struct InputOp* op) {
  int mode = op->modes % 100;
  int val = op->val;
  int addr = op->targ;
  assert(mode % 10 == 0);
  assert(addr >= 0);
  machine->regs[addr] = val;
}

void exec_output(struct Machine* machine, struct OutputOp* op) {
  int mode = op->modes % 10;
  int val = mode == 1 ? op->val : machine->regs[op->val];
  machine->put_output(val);
}

void exec_add(struct Machine* machine, struct AddOp* op) {
  int mode_1 = op->modes % 10;
  int mode_2 = op->modes / 10 % 10;

  int a = mode_1 == 1 ? op->a : machine->regs[op->a];
  int b = mode_2 == 1 ? op->b : machine->regs[op->b];
  int addr = op->targ;

  assert(addr >= 0);
  machine->regs[addr] = a + b;
}

void exec_mult(struct Machine* machine, struct MultOp* op) {
  int mode_1 = op->modes % 10;
  int mode_2 = op->modes / 10 % 10;

  int a = mode_1 == 1 ? op->a : machine->regs[op->a];
  int b = mode_2 == 1 ? op->b : machine->regs[op->b];
  int addr = op->targ;

  assert(addr >= 0);
  machine->regs[addr] = a * b;
}

struct Op* parse_op(struct Machine* machine, int op_code) {
  union Instruction* instruction = malloc(sizeof(union Instruction));
  struct Op* op = malloc(sizeof(struct Op));
  int code = op_code % 10;
  int modes = op_code / 100;
  switch(code) {
    case ADD: ;
      struct AddOp* add_op = malloc(sizeof(struct AddOp));
      add_op->a = step(machine);
      add_op->b = step(machine);
      add_op->targ = step(machine);

      add_op->modes = modes;

      instruction->add_op = add_op;
      op->op_type = ADD;
      break;
    case INPUT: ;
      struct InputOp* input_op = malloc(sizeof(struct InputOp));
      input_op->targ = step(machine);
      input_op->val = machine->get_input();

      input_op->modes = modes;

      instruction->input_op = input_op;
      op->op_type = INPUT;
      break;
    case OUTPUT: ;
      struct OutputOp* output_op = malloc(sizeof(struct OutputOp));
      output_op->val = step(machine);

      output_op->modes = modes;

      instruction->output_op = output_op;
      op->op_type = OUTPUT;
      break;
    case MULT: ;
      struct MultOp* mult_op = malloc(sizeof(struct MultOp));
      mult_op->a = step(machine);
      mult_op->b = step(machine);
      mult_op->targ = step(machine);

      mult_op->modes = modes;

      instruction->mult_op = mult_op;
      op->op_type = MULT;
  }

  op->instruction = instruction;
  return op;
}

void eval(struct Machine* machine, struct Op* op) {
  switch(op->op_type) {
    case INPUT:
      exec_input(machine, op->instruction->input_op);
      break;
    case OUTPUT:
      exec_output(machine, op->instruction->output_op);
      break;
    case ADD:
      exec_add(machine, op->instruction->add_op);
      break;
    case MULT:
      exec_mult(machine, op->instruction->mult_op);
      break;
  }
}

int run(struct Machine* machine) {
  int op_code = step(machine);
  while(op_code != HALT) {
    struct Op* op = parse_op(machine, op_code);
    eval(machine, op);
    op_code = step(machine);
  }

  assert(op_code == HALT);
  printf("WE'RE GONNA SHUT 'ER DOWN");

  return 0;
}
