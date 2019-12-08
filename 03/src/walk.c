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

int find_man_dist_to_origin(struct Point point) {
  return abs(point.x) + abs(point.y);
}

int find_least_dist(struct PointList* table[H_TABLE_SIZE]) {
  int ans = -1;
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    if (table[i] != NULL) {
      struct PointList* list = table[i];
      struct PointNode* node = list->head;
      while(node != NULL) {
        struct Point pt = *(node->point);
        int dist = find_man_dist_to_origin(pt); 
        if (ans < 0 || dist < ans) {
          ans = dist;
        };

        node = node->next;
      }
    }
  }
  return ans;
}

int find_distance_to_closest_intersection(struct OpList* a, struct OpList* b) {
  struct PointSet* seen_pts = build_seen_pt_set(a);
  struct PointSet* other_seen_pts = build_seen_pt_set(b);

  struct PointSet* intersections = find_intersections(seen_pts, other_seen_pts);
  int answer = find_least_dist(intersections->h_table);
  printf("%d\n", intersections->h_table[0]->head->point->x);
  return answer;
}
