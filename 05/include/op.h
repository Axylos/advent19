#ifndef FILE_OP_SEEN
#define FILE_OP_SEEN

#include <stdio.h>

#define ADD 1
#define MULT 2
#define INPUT 3
#define OUTPUT 4
#define HALT 99

struct AddOp {
  int a;
  int b;
  int targ;
  int modes;
};

struct MultOp {
  int a;
  int b;
  int targ;
  int modes;
};

struct InputOp {
  int val;
  int targ;
  int modes;
};

struct OutputOp {
  int val;
  int modes;
};

union Instruction {
  struct AddOp* add_op;
  struct MultOp* mult_op;
  struct InputOp* input_op;
  struct OutputOp* output_op;
};

struct Op {
  int op_type;
  union Instruction* instruction;
};

#endif
