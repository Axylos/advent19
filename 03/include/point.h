#ifndef FILE_POINT_H_SEEN
#define FILE_POINT_H_SEEN
#define H_TABLE_SIZE 50

#include <stdlib.h>
#include <stdbool.h>

struct Point {
  int x;
  int y;
  int steps;
};

struct PointList {
  struct PointNode* head;
  struct PointNode* tail;
};

struct PointNode {
  struct Point* point;
  struct PointNode* next;
};

struct PointSet {
  struct PointList* h_table[H_TABLE_SIZE]; 
};

struct PointSet* find_intersections(struct PointSet* a, struct PointSet* b);

struct Point* init_pt(int x, int y);

struct PointSet* init_pt_set();
struct Point* has_key(struct PointSet* set, struct Point* pt);
void set_insert_pt(struct PointSet* set, struct Point* pt);

void append_pt(struct PointList* list, struct Point* pt);

struct PointList* init_pt_list();
#endif


