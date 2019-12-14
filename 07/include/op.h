#ifndef FILE_OP_SEEN
#define FILE_OP_SEEN

#include <stdio.h>


enum OpSig  {
  ADD=1,
  MULT=2,
  INPUT=3,
  OUTPUT=4,
  JUMP_IF_TRUE=5,
  JUMP_IF_FALSE=6,
  LESS_THAN=7,
  EQUALS=8,
  HALT=99,
  GO=100,
  PAUSE=101,
  NOOP=-1,
};

union BinaryOp {
  long a;
  long b;
  long addr;
};

struct UnoOp {
  long val;
};

struct BiOp {
  long val;
  long addr;
};

struct TriOp {
  long a;
  long b;
  long addr;
};

union Instruction {
  enum OpSig null_op;
  struct UnoOp uno_op;
  struct BiOp bi_op;
  struct TriOp tri_op;
};

struct Op {
  enum OpSig op_sig;
  int modes;
  union Instruction instruction;
};

#endif
