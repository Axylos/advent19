#ifndef FILE_OP_SEEN
#define FILE_OP_SEEN

#include <stdio.h>

#define ADD 1
#define MULT 2
#define INPUT 3
#define OUTPUT 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS_THAN 7
#define EQUALS 8
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

struct JumpIfTrueOp {
  int test_val;
  int addr;
  int modes;
};

struct JumpIfFalseOp {
  int test_val;
  int addr;
  int modes;
};

struct LessThanOp {
  int a;
  int b;
  int addr;
  int modes;
};

struct EqualsOp {
  int a;
  int b;
  int addr;
  int modes;
};

union Instruction {
  struct AddOp* add_op;
  struct MultOp* mult_op;
  struct InputOp* input_op;
  struct OutputOp* output_op;
  struct JumpIfTrueOp* jump_if_true_op;
  struct JumpIfFalseOp* jump_if_false_op;
  struct LessThanOp* less_than_op;
  struct EqualsOp* equals_op;
};

struct Op {
  int op_type;
  union Instruction* instruction;
};

#endif
