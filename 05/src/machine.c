#include <op.h>
#include <machine.h>
#include <stdlib.h>
#include <assert.h>



struct Machine* init_machine(int* op_list, int list_size,
  void* data_ptr) {
  struct Machine* machine = malloc(sizeof(struct Machine));
  machine->ip = 0;
  machine->regs = op_list;
  machine->data_ptr = data_ptr;
  machine->reg_size = list_size;
  machine->state = GO_SIG;

  return machine;
}

void print_regs(struct Machine* m) {
  for (int i = 0; i < m->reg_size; i++) {
    printf("%d  ", m->regs[i]);
  }

  printf("\n\n");
  printf("ip: %d ip_val: %d\n", m->ip - 1, m->regs[m->ip - 1]);
}

int step(struct Machine* machine) {
  return machine->ip >= machine->reg_size ? NOOP : machine->regs[machine->ip++];
}

int exec_input(struct Machine* machine, struct InputOp op) {
  int mode = op.modes % 100;
  enum OpSig sig = GO_SIG;
  int val = machine_reader(machine->data_ptr, &sig);
  int addr = op.targ;
  assert(mode % 10 == 0);
  assert(addr >= 0);
  machine->regs[addr] = val;

  return sig;
}

int exec_output(struct Machine* machine, struct OutputOp op) {
  int mode = op.modes % 10;
  int val = mode == 1 ? op.val : machine->regs[op.val];
  return machine_writer(machine->data_ptr, val);
}

void exec_add(struct Machine* machine, struct AddOp op) {
  int mode_1 = op.modes % 10;
  int mode_2 = op.modes / 10 % 10;

  int a = mode_1 == 1 ? op.a : machine->regs[op.a];
  int b = mode_2 == 1 ? op.b : machine->regs[op.b];
  int addr = op.targ;

  assert(addr >= 0);
  machine->regs[addr] = a + b;
}

void exec_jump_true(struct Machine* machine, struct JumpIfTrueOp op) {
  int mode_1 = op.modes % 10;
  int mode_2 = op.modes / 10 % 10;

  int test_val = mode_1 == 1 ? op.test_val : machine->regs[op.test_val];
  int addr = mode_2 == 1 ? op.addr : machine->regs[op.addr];

  assert(addr >= 0);
  if (test_val != 0) {
    machine->ip = addr;
  }
}

void exec_jump_false(struct Machine* machine, struct JumpIfFalseOp op) {
  int mode_1 = op.modes % 10;
  int mode_2 = op.modes / 10 % 10;

  int test_val = mode_1 == 1 ? op.test_val : machine->regs[op.test_val];
  int addr = mode_2 == 1 ? op.addr : machine->regs[op.addr];

  assert(addr >= 0);
  if (test_val == 0) {
    machine->ip = addr;
  }
}

void exec_less_than(struct Machine* machine, struct LessThanOp op) {
  int mode_1 = op.modes % 10;
  int mode_2 = op.modes / 10 % 10;

  int a = mode_1 == 1 ? op.a : machine->regs[op.a];
  int b = mode_2 == 1 ? op.b : machine->regs[op.b];
  int addr = op.addr;

  assert(addr >= 0);
  if (a < b) {
    machine->regs[addr] = 1;
  } else {
    machine->regs[addr] = 0;
  }
}
void exec_equals(struct Machine* machine, struct EqualsOp op) {
  int mode_1 = op.modes % 10;
  int mode_2 = op.modes / 10 % 10;

  int a = mode_1 == 1 ? op.a : machine->regs[op.a];
  int b = mode_2 == 1 ? op.b : machine->regs[op.b];
  int addr = op.addr;

  assert(addr >= 0);
  if (a == b) {
    machine->regs[addr] = 1;
  } else {
    machine->regs[addr] = 0;
  }

}


void exec_mult(struct Machine* machine, struct MultOp op) {

  int mode_1 = op.modes % 10;
  int mode_2 = op.modes / 10 % 10;

  int a = mode_1 == 1 ? op.a : machine->regs[op.a];
  int b = mode_2 == 1 ? op.b : machine->regs[op.b];
  int addr = op.targ;

  assert(addr >= 0);
  machine->regs[addr] = a * b;
}

struct Op parse_op(struct Machine* machine, int op_code) {
  union Instruction instruction;
  struct Op op;
  int code = op_code % 100;
  int modes = op_code / 100;
  switch(code) {
    case ADD: ;
      struct AddOp add_op;
      add_op.a = step(machine);
      add_op.b = step(machine);
      add_op.targ = step(machine);

      add_op.modes = modes;

      instruction.add_op = add_op;
      op.op_type = ADD;
      break;
    case INPUT: ;
      struct InputOp input_op;
      input_op.targ = step(machine);

      input_op.modes = modes;

      instruction.input_op = input_op;
      op.op_type = INPUT;
      break;
    case OUTPUT: ;
      struct OutputOp output_op;
      output_op.val = step(machine);

      output_op.modes = modes;

      instruction.output_op = output_op;
      op.op_type = OUTPUT;
      break;
    case MULT: ;
      struct MultOp mult_op;
      mult_op.a = step(machine);
      mult_op.b = step(machine);
      mult_op.targ = step(machine);

      mult_op.modes = modes;

      instruction.mult_op = mult_op;
      op.op_type = MULT;
      break;
    case JUMP_IF_TRUE:
      ;;
      struct JumpIfTrueOp jt_op;
      jt_op.test_val = step(machine);
      jt_op.addr = step(machine);

      jt_op.modes = modes;

      instruction.jump_if_true_op = jt_op;
      op.op_type = JUMP_IF_TRUE;
      break;

      break;
    case JUMP_IF_FALSE:
      ;;
      struct JumpIfFalseOp jf_op;
      jf_op.test_val = step(machine);
      jf_op.addr = step(machine);

      jf_op.modes = modes;

      instruction.jump_if_false_op = jf_op;
      op.op_type = JUMP_IF_FALSE;
      break;
    case LESS_THAN:
      ;;
      struct LessThanOp lt_op;
      lt_op.a = step(machine);
      lt_op.b = step(machine);
      lt_op.addr = step(machine);

      lt_op.modes = modes;

      instruction.less_than_op = lt_op;
      op.op_type = LESS_THAN;
      break;
    case EQUALS: 
      ;;
      struct EqualsOp eq_op;
      eq_op.a = step(machine);
      eq_op.b = step(machine);
      eq_op.addr = step(machine);

      eq_op.modes = modes;

      instruction.equals_op = eq_op;
      op.op_type = EQUALS;
      break;
    case HALT:
      op.op_type = HALT;
      machine->state = HALT_SIG;
      break;
  }

  op.instruction = instruction;
  return op;
}

int eval(struct Machine* machine, struct Op op) {
  enum OpSig sig = GO_SIG;
  switch(op.op_type) {
    case INPUT:
      sig = exec_input(machine, op.instruction.input_op);
      break;
    case OUTPUT:
      sig = exec_output(machine, op.instruction.output_op);
      break;
    case ADD:
      exec_add(machine, op.instruction.add_op);
      break;
    case MULT:
      exec_mult(machine, op.instruction.mult_op);
      break;
    case JUMP_IF_TRUE:
      exec_jump_true(machine, op.instruction.jump_if_true_op);
      break;
    case JUMP_IF_FALSE: 
      exec_jump_false(machine, op.instruction.jump_if_false_op);
      break;
    case LESS_THAN:
      exec_less_than(machine, op.instruction.less_than_op);
      break;
    case EQUALS:
      exec_equals(machine, op.instruction.equals_op);
      break;
    case HALT:
      machine->state = HALT_SIG;
      sig = HALT_SIG;
      break;
    case NOOP:
      puts("got a noop");
    default:
      puts("you broke it");
      assert(0);
  }

  return sig;
}

int run(struct Machine* machine) {
  while(machine->state == GO_SIG) {
    int op_code = step(machine);
    printf("op code: %d\n", op_code);
    struct Op op = parse_op(machine, op_code);
    machine->state = eval(machine, op);
  }
  printf("final sig: %d\n", machine->state);

  printf("WE'RE GONNA SHUT 'ER DOWN\n");
  return machine->state == HALT_SIG ? HALT_SIG : GO_SIG;
}
