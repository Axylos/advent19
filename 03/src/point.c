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


  append_pt(set->h_table[code], new_pt);

  pt->x = new_pt->x;
  pt->y = new_pt->y;
}

bool has_key(struct PointSet* set, struct Point* pt) {
  int code = hash(pt);

  struct PointList* list = set->h_table[code];
  struct PointNode* head = list->head;
  while(head != NULL) {
    if (cmp(head->point, pt)) {
      return true;
    }

    head = head->next;
  }

  return false;
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
        if (has_key(b, pt)) {
          // printf("intersection x: %d y: %d", pt->x, pt->y);
          set_insert_pt(intersection, pt);
        }
        node = node->next;
      }
    }
  }
  
  return intersection;
}
