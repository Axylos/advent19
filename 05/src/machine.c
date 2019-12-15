#include <op.h>
#include <machine.h>
#include <stdlib.h>
#include <assert.h>

void resize_machine(struct Machine* m, int addr) {
  assert(addr >= m->reg_size);
  int new_size = addr + 1;
  m->regs = realloc(m->regs, new_size * sizeof(long));
  m->reg_size = new_size;
}

void set_reg(struct Machine* m, long val, int addr) {
  assert(addr < m->reg_size);
  m->regs[addr] = val;
}

struct Machine* init_machine(long* op_list, int list_size,
  void* data_ptr) {
  struct Machine* machine = malloc(sizeof(struct Machine));
  machine->ip = 0;
  machine->regs = op_list;
  machine->data_ptr = data_ptr;
  machine->reg_size = list_size;
  machine->state = GO;
  machine->rel_base = 0;

  return machine;
}

void print_regs(struct Machine* m) {
  for (int i = 0; i < m->reg_size; i++) {
    printf("%ld  ", m->regs[i]);
  }

  printf("\n\n");
  printf("ip: %d ip_val: %ld\n", m->ip - 1, m->regs[m->ip - 1]);
}

long step(struct Machine* machine) {
  return machine->ip >= machine->reg_size ? NOOP : machine->regs[machine->ip++];
}

long get_idx(struct Machine* m, long val, int mode) {
  int addr;
  switch (mode) {
    case 0:
      addr = val;
      break;
    case 2:
      addr = val + m->rel_base;
      break;
  }

  if (m->reg_size <= addr) {
    resize_machine(m, addr);
  }

  return addr; 
}

long get_val(struct Machine* m, long val, int mode) {
  if (mode == 0 || mode == 2) {
    long addr = get_idx(m, val, mode);
    val = m->regs[addr];
  }

  return val;
}

int exec_input(struct Machine* machine, struct UnoOp op, int mode) {
  enum OpSig sig = GO;
  long val = machine_reader(machine->data_ptr, &sig);
  long addr = get_idx(machine, op.val, mode);
  assert(addr >= 0);
  set_reg(machine, val, addr);

  return sig;
}

long exec_output(struct Machine* machine, struct UnoOp op, int mode) {
  long val = get_val(machine, op.val, mode);
  return machine_writer(machine->data_ptr, val);
}

void exec_add(struct Machine* machine, struct TriOp op, int modes) {

  int mode_a = modes % 10;
  int mode_b = (modes / 10) % 10;
  int mode_c = (modes / 100) % 10;
  long a = get_val(machine, op.a, mode_a);
  long b = get_val(machine, op.b, mode_b);
  long addr = get_idx(machine, op.addr, mode_c);

  assert(addr >= 0);
  set_reg(machine, a + b, addr);
}

void exec_jump_true(struct Machine* machine, struct BiOp op, int modes) {
  int mode_a = modes % 10;
  int mode_b = (modes / 10) % 10;
  long test_val = get_val(machine, op.val, mode_a);
  long addr = get_val(machine, op.addr, mode_b);

  assert(addr >= 0);
  if (test_val != 0) {
    machine->ip = addr;
  }
}

void exec_jump_false(struct Machine* machine, struct BiOp op, int modes) {
  int mode_a = modes % 10;
  int mode_b = (modes / 10) % 10;
  long test_val = get_val(machine, op.val, mode_a);
  long addr = get_val(machine, op.addr, mode_b);

  assert(addr >= 0);
  if (test_val == 0) {
    machine->ip = addr;
  }
}

void exec_less_than(struct Machine* machine, struct TriOp op, int modes) {
  int mode_a = modes % 10;
  int mode_b = (modes / 10) % 10;
  int mode_c = (modes / 100) % 10;
  long a = get_val(machine, op.a, mode_a);
  long b = get_val(machine, op.b, mode_b);
  long addr = get_idx(machine, op.addr, mode_c);

  assert(addr >= 0);
  if (a < b) {
    set_reg(machine, 1, addr);
  } else {
    set_reg(machine, 0, addr);
  }
}
void exec_equals(struct Machine* machine, struct TriOp op, int modes) {
  int mode_a = modes % 10;
  int mode_b = (modes / 10) % 10;
  int mode_c = (modes / 100) % 10;

  long a = get_val(machine, op.a, mode_a);
  long b = get_val(machine, op.b, mode_b);
  long addr = get_idx(machine, op.addr, mode_c);

  assert(addr >= 0);
  if (a == b) {
    set_reg(machine, 1, addr);
  } else {
    set_reg(machine, 0, addr);
  }

}

void exec_set_base(struct Machine* m, struct UnoOp op, int modes) {
  int mode = modes % 10;
  long base = m->rel_base;

  int addr;
  if (mode == 0) {
    addr = get_idx(m, op.val, 0);
    base += m->regs[addr];
  } else if (mode == 1) {
    base += op.val;
  } else if (mode == 2) {
    addr = get_idx(m, op.val + m->rel_base, 0);
    base += m->regs[addr];
  } else {
    puts("wrongw base arg");
    assert(0);
  }

  m->rel_base = base;
}

void exec_mult(struct Machine* machine, struct TriOp op, int modes) {
  int mode_a = modes % 10;
  int mode_b = (modes / 10) % 10;
  int mode_c = (modes / 100) % 10;

  long a = get_val(machine, op.a, mode_a);
  long b = get_val(machine, op.b, mode_b);
  long addr = get_idx(machine, op.addr, mode_c);

  assert(addr >= 0);
  set_reg(machine, a * b, addr);
  machine->regs[addr] = a * b;
}

long construct_val(struct Machine* m, int mode, long val) {
  long addr;
  switch(mode) {
    case 0:
      ;;
      addr = m->regs[val];
      if (addr >= m->reg_size) {
        resize_machine(m, addr);
      }
    
      return m->regs[addr];
    case 1:
      return val;
    case 2:
      ;;
      addr = val + m->rel_base;
      if (addr >= m->reg_size) {
        resize_machine(m, addr);
      }

      return m->regs[addr];
  }

  assert(0);
  return -1;
}

struct TriOp build_tri_op(struct Machine* m) {
  struct TriOp op;
  op.a = step(m);
  op.b = step(m);
  op.addr = step(m);

  return op;
}

struct BiOp build_bi_op(struct Machine* m) {
  struct BiOp op;

  op.val = step(m);
  op.addr = step(m);

  return op;
}

struct UnoOp build_uno_op(struct Machine* m) {
  struct UnoOp op;

  op.val = step(m);

  return op;
}

struct Op parse_op(struct Machine* m, int op_code) {
    union Instruction instruction;
    struct Op op;
    int code = op_code % 100;
    int modes = op_code / 100;
    op.op_sig = code;

  switch(code) {
    case ADD:
      ;;
      struct TriOp add_op = build_tri_op(m);
      instruction.tri_op = add_op;
      break;
    case MULT:
      ;;
      struct TriOp mult_op = build_tri_op(m);
      instruction.tri_op = mult_op;
      break;
    case OUTPUT:
      ;;
      struct UnoOp output_op = build_uno_op(m);
      instruction.uno_op = output_op;
      break;
    case INPUT:
      ;;
      struct UnoOp input_op = build_uno_op(m);
      instruction.uno_op = input_op;
      break;
    case  JUMP_IF_TRUE:
      ;;
      struct BiOp jt = build_bi_op(m);
      instruction.bi_op = jt;
      break;
    case JUMP_IF_FALSE:
      ;;
      struct BiOp jf = build_bi_op(m);
      instruction.bi_op = jf;
      break;
    case LESS_THAN:
      ;;
      struct TriOp lt = build_tri_op(m);
      instruction.tri_op = lt;
      break;
    case EQUALS:
      ;;
      struct TriOp eq = build_tri_op(m);
      instruction.tri_op = eq;
      break;
    case SET_BASE:
      ;;
      struct UnoOp base = build_uno_op(m);
      instruction.uno_op = base;
      break;
    case HALT:
      instruction.null_op = HALT;
      break;
  }

  op.modes = modes;
  op.instruction = instruction;
  return op;
}

int eval(struct Machine* machine, struct Op op) {
  enum OpSig sig = GO;
  switch(op.op_sig) {
    case INPUT:
      sig = exec_input(machine, op.instruction.uno_op, op.modes);
      break;
    case OUTPUT:
      sig = exec_output(machine, op.instruction.uno_op, op.modes);
      break;
    case ADD:
      exec_add(machine, op.instruction.tri_op, op.modes);
      break;
    case MULT:
      exec_mult(machine, op.instruction.tri_op, op.modes);
      break;
    case JUMP_IF_TRUE:
      exec_jump_true(machine, op.instruction.bi_op, op.modes);
      break;
    case JUMP_IF_FALSE: 
      exec_jump_false(machine, op.instruction.bi_op, op.modes);
      break;
    case LESS_THAN:
      exec_less_than(machine, op.instruction.tri_op, op.modes);
      break;
    case EQUALS:
      exec_equals(machine, op.instruction.tri_op, op.modes);
      break;
    case SET_BASE:
      exec_set_base(machine, op.instruction.uno_op, op.modes);
      break;
    case HALT:
      machine->state = HALT;
      sig = HALT;
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
  while(machine->state == GO) {
    int op_code = step(machine);
    struct Op op = parse_op(machine, op_code);
    machine->state = eval(machine, op);
  }

  //printf("WE'RE GONNA SHUT 'ER DOWN\n");
  return machine->state;
}
