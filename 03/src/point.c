#include <point.h>
#include <op.h>
#include <stdbool.h>
#include <stdio.h>

int hash(struct Point* pt) {
  return ((pt->x + pt->y) * 31) % H_TABLE_SIZE;
}

struct PointSet* init_pt_set() {
  struct PointList* table[H_TABLE_SIZE];

  struct PointSet* set = malloc(sizeof(struct PointSet));
  set->h_table = table;

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
