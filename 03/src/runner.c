#include <stdio.h>
#include <stdlib.h>
#include <circuit.h>
#include <stdbool.h>

#define SIZE 30



#define UP 'U'
#define RIGHT 'R'
#define DOWN 'D'
#define LEFT 'L'

struct Op {
  char dir;
  int dist;
};

struct Node {
  struct Node* next;
  struct Op* val;
};

struct Node* h_table[SIZE];

bool cmp(struct Op* a, struct Op* b) {
  return a->dist == b->dist && a->dir == b->dir;
}

int hash(struct Op* op) {
  return op->dist % SIZE; //ha ha
}

bool has_key(struct Op* op) {
  int code = hash(op);

  struct Node* head = h_table[code];
  while(head != NULL) {
    if (cmp(head->val, op)) {
      return true;
    }

    head = head->next;
  }

  return false;
}

void insert_val(struct Op* op) {
  int hash_code = hash(op);
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

struct Node* parse_line() {
  char dir;
  int dist;

  struct Node* head = NULL;

  char terminal;
  while(scanf("%c%d%c", &dir, &dist, &terminal)!= EOF) {
    struct Op* op = (struct Op*)malloc(sizeof(struct Op));
    op->dir = dir;
    op->dist = dist;

    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = op;
    node->next = NULL;
    if (head == NULL) {
      head = node;
    } else {
     node->next = head; 
     head = node;
    }
    if (terminal != ',') {
      break;
    }

    terminal = 'a';
  }

  return head;
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

  printf("%d\n", h_table[0]->val->dist);
  printf("%d\n", a->val->dist);
  printf("%d\n", b->val->dist);
  printf("has val: %d", has_key(b->val));
  return 0;
}
