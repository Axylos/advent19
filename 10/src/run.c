#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

enum cell_type {
  EMPTY,
  ASTEROID
};

struct Point {
  unsigned short x;
  unsigned short y;
};

struct Cell {
  struct Point pt;
  enum cell_type type;
  int id;
  struct Point neighbors[10];
};

struct Node {
  struct Cell val;
  struct Node* next;
};

struct List {
  struct Node* head;
  struct Node* tail;
};

struct List* init_list()
{
  struct List* list = malloc(sizeof(struct List));
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void append(struct List* list, struct Cell cell) {
  struct Node* node = malloc(sizeof(struct Node));
  node->val = cell;
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    list->tail = node;
  }
}

int main(int argc, char* argv[])
{
  puts("here");
  struct List* list = init_list();

  int line_no = 0;
  int col_no = 0;
  char line[150];
  int empty_id = 0;
  int asteroid_id = 0;
  while(fgets(line, 150, stdin) != NULL) {
    char* ch;
    for (ch = line; *ch != '\0'; ch++) {
      struct Point pt = { col_no, line_no };
      struct Cell cell;
      cell.pt = pt;
      if (*ch == '#') {
        cell.type = ASTEROID;
        cell.id = asteroid_id++;
      } else {
        cell.type = EMPTY;
        cell.id = empty_id++;
      }

      append(list, cell);
      col_no++;
    }
    line_no++;
  }
  int grid[10][10];
  grid[5][5] = 1;

  struct Point vals[50][50];

  struct Point pt = {
    0, 0
  };
  vals[0][0] = pt;
  struct Point foo = vals[0][0];
  printf("%d %d\n", foo.x, foo.y);

  struct Cell edges[342][360];
  puts("here");
  edges[0][0] = list->head->val;
  printf("%d\n", grid[5][5]);
  printf("%d\n", edges[0][0].pt.y);
  printf("size of pt: %ld\n", sizeof(struct Point));
}
