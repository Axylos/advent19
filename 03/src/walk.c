#include <walk.h>
#include <point.h>
#include<op.h>
#include <stdio.h>

void walk(struct PointSet* set, struct Point* pos, char dir, int dist) {
  if (dist < 1) {
    return;
  }
  switch(dir) {
    case UP:
      pos->y += 1;
      break;
    case DOWN:
      pos->y -= 1;
      break;
    case LEFT:
      pos->x -= 1;
      break;
    case RIGHT:
      pos->x += 1;
      break;
  }

  set_insert_pt(set, pos);
  walk(set, pos, dir, dist - 1);
}

struct PointSet* build_seen_pt_set(struct OpList* ops) {
  struct Point pos = {
    0,
    0
  };

  struct PointSet* set = init_pt_set();
  struct OpNode* head = ops->head;
  while(head != NULL) {
    struct Op* op = head->val;
    walk(set, &pos, op->dir, op->dist);
    head = head->next;
  }

  return set;
}
