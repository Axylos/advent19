#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <nodes.h>
#include <assert.h>

#define H_TABLE_SIZE 50

char* ROOT_CODE = "COM";
struct ListNode* node_table[H_TABLE_SIZE];

int hash(char code[4]) {
  return code[0] * code[1] * code[2] % H_TABLE_SIZE;
}

int insert_node(struct ListNode* table[H_TABLE_SIZE], struct TreeNode* node) {
  char* key = node->code;
  int hashed = hash(key);

  if (!table[hashed]) {
    struct ListNode* head = malloc(sizeof(struct ListNode));
    head->val = node;
    head->next = NULL;
    table[hashed] = head;
  } else {
    struct ListNode* head = table[hashed];
    if (strcmp(head->val->code, node->code) == 0) {
      return 0;
    }

    while (head->next != NULL) {
      head = head->next;
      if (strcmp(head->val->code, node->code) == 0) {
        return 0;
      }
    }

    struct ListNode* new_node = malloc(sizeof(struct ListNode));
    new_node->val = node;
    new_node->next = NULL;
    head->next = new_node;
  }
  return 1;
}

struct TreeNode* table_lookup(struct ListNode* table[H_TABLE_SIZE], char key[4]) {
  int code = hash(key);
  struct ListNode* head = table[code];
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    while (head != NULL) {
      if (strcmp(key, head->val->code) == 0) {
        return head->val;
      }

      head = head->next;
    }
  }
  return NULL;
}
int find_node_height(struct ListNode* table[H_TABLE_SIZE], struct TreeNode* node) {
  if (strcmp(node->parent_code, ROOT_CODE) == 0) {
    return 1;
  } else if (node->height > -1) {
    return node->height;
  } else {
    struct TreeNode* parent_node = table_lookup(table, node->parent_code); 
    assert(parent_node != NULL);
    return find_node_height(table, parent_node) + 1;
  }
}


void compute_heights(struct ListNode* table[H_TABLE_SIZE]) {
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    struct ListNode* head = table[i];
    while (head != NULL) {
      struct TreeNode* node = table_lookup(table, head->val->code);
      int height = find_node_height(table, node);
      head->val->height = height;
      head = head->next;
    }
  }
}

int sum_heights(struct ListNode* table[H_TABLE_SIZE]) {
  int sum = 0;
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    struct ListNode* head = table[i];
    while (head != NULL) {
      sum += head->val->height;
      head = head->next;
    }
  }

  return sum;
}

int main(int argc, char* argv[]) {
  char parent_code[4];
  char child_code[4];

  while (scanf("%3s)%3s", parent_code, child_code) != EOF) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));

    strcpy(node->code, child_code);
    strcpy(node->parent_code, parent_code);
    node->height = -1;
    assert(insert_node(node_table, node) != 0);
  }

  compute_heights(node_table);

  int sum = sum_heights(node_table);
  printf("The sum of all node heights is: %d\n", sum);
  return 0;
}
