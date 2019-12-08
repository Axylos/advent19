#ifndef FILE_OP_H_SEEN
#define FILE_OP_H_SEEN
#include <stdbool.h>
#include <point.h>

#define UP 'U'
#define RIGHT 'R'
#define DOWN 'D'
#define LEFT 'L'

struct Op {
  char dir;
  int dist;
};

struct OpNode {
  struct OpNode* next;
  struct Op* val;
};

bool cmp(struct Point* a, struct Point* b);

struct OpList {
  struct OpNode* head;
  struct OpNode* tail;
};

struct OpList* init_op_list();

void append_op(struct OpList* list, struct Op* op);

struct OpList* parse_line();
#endif
