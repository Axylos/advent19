#include <stdio.h>
#include <stdlib.h>
#include <circuit.h>
#include <stdbool.h>
#include <op.h>
#include <walk.h>
/*
void insert_val(struct Op* op) {
  int hash_code = 1; //hash(op);
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));
  node->val = op;
  node->next = NULL;
  if (h_table[hash_code] == NULL) {
    h_table[hash_code] = node;
  } else {
    struct Node* head = h_table[hash_code];
    while(head->next != NULL) {
      head = head->next;
    }

    head->next = node;
  }
}

int main(int argc, char* argv[]) {
  //char direction;
  //int dist;

  struct Node* a = parse_line();
  struct Node* b = parse_line();

  struct Node* head = a;

  while(head->next != NULL) {
    insert_val(head->val);
    head = head->next;
  }

  struct Node* intersections;

  head = b;

  while(head != NULL) {
    if (has_key(head->val)) {
      struct Node* node = malloc(sizeof(struct Node));
      node->val = head->val;
      node->next = NULL;
      if (intersections == NULL) {
        intersections = node;
      } else {
        node->next = intersections;
        intersections = node;
      }
    }

    head = head->next;
  }

  printf("%d\n", h_table[0]->val->dist);
  printf("%d\n", a->val->dist);
  printf("%d\n", b->val->dist);
  printf("has val: %d", has_key(b->val));
  return 0;
}
*/

int main(int argc, char* argv[]) {
  struct OpList* a = parse_line();
  struct OpList* b = parse_line();

  struct PointSet* seen_pts = build_seen_pt_set(a);
  struct PointSet* other_seen_pts = build_seen_pt_set(b);

  struct PointSet* intersections = find_intersections(seen_pts, other_seen_pts);

  int dist = find_distance_to_closest_intersection(intersections);
  printf("the answer to part I is: %d\n", dist);
  int steps = find_fewest_steps(intersections);
  printf("the answer to part II is: %d\n", steps);

  /*
  struct PointSet* intersection_points = find_intersections(seen_pts, other_seen_pts);
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    if ()intersection_points->h_table[i] != NULL) {
      printf("%d\n", intersection_points->h_table[i]->head->point->x);
    }
  }
  */
  //printf("%d\n", set->h_table[1]->head->point->x);
  return 0;
}
