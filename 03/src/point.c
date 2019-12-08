#include <point.h>
#include <op.h>
#include <stdbool.h>
#include <stdio.h>

int hash(struct Point* pt) {
  return abs(((pt->x + pt->y) * 31) % H_TABLE_SIZE);
}

struct PointSet* init_pt_set() {
  struct PointSet* set = malloc(sizeof(struct PointSet));
  return set;
}

void set_insert_pt(struct PointSet* set, struct Point* pt) {
  int code = hash(pt);
  if (set->h_table[code] == NULL) {
    set->h_table[code] = init_pt_list();
  }

  struct Point* new_pt = malloc(sizeof(struct Point));
  new_pt->x = pt->x;
  new_pt->y = pt->y;
  new_pt->steps = pt->steps;

  append_pt(set->h_table[code], new_pt);

  pt->x = new_pt->x;
  pt->y = new_pt->y;
}

struct Point* has_key(struct PointSet* set, struct Point* pt) {
  int code = hash(pt);

  struct PointList* list = set->h_table[code];
  struct PointNode* head = list->head;
  while(head != NULL) {
    if (cmp(head->point, pt)) {
      return head->point;
    }

    head = head->next;
  }

  return NULL;
}

void append_pt(struct PointList* list, struct Point* pt) {
  struct PointNode* node = malloc(sizeof(struct PointNode));
  node->point = pt;
  node->next = NULL;
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

struct PointList* init_pt_list() {
  struct PointList* list = malloc(sizeof(struct PointList));
  list->head = NULL;
  list->tail = NULL;


  return list;
}

struct PointSet* find_intersections(struct PointSet* a, struct PointSet* b) {
  struct PointSet* intersection = init_pt_set();
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    if (a->h_table[i] != NULL) {
      struct PointNode* node = a->h_table[i]->head;
      while(node != NULL) {
        struct Point* pt = node->point;
        struct Point* other_pt;
        if ((other_pt = has_key(b, pt))) {
          struct Point* intersection_pt = malloc(sizeof(struct Point));
          intersection_pt->x = pt->x;
          intersection_pt->y = pt->y;
          intersection_pt->steps = pt->steps + other_pt->steps;

          set_insert_pt(intersection, intersection_pt);
        }
        node = node->next;
      }
    }
  }
  
  return intersection;
}
