#include <op.h>
#include <stdio.h>
#include <stdlib.h>


bool cmp(struct Point* a, struct Point* b) {
  return a->x == b->x && a->y == b->y;
}

struct OpList* parse_line() {
  struct OpList* list = init_op_list();
  char dir;
  int dist;

  char terminal;
  while(scanf("%c%d%c", &dir, &dist, &terminal)!= EOF) {
    struct Op* op = (struct Op*)malloc(sizeof(struct Op));
    op->dir = dir;
    op->dist = dist;

    append_op(list, op);
    if (terminal != ',') {
      break;
    }

    terminal = 'a';
  }

  return list;
}

struct OpList* init_op_list() {
  struct OpList* list = malloc(sizeof(struct OpList));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void append_op(struct OpList* list, struct Op* op) {
  struct OpNode* node = malloc(sizeof(struct OpNode));
  node->next = NULL;
  node->val = op;

  if (list->head == NULL) {
    list->head = node;
  } else if (list->tail == NULL) {
    list->head->next = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}
