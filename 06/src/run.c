#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <nodes.h>
#include <assert.h>
#include <stdbool.h>
#include <tree.h>

int main(int argc, char* argv[]) {

  char* ROOT_CODE = "COM";
  struct ListNode* node_table[H_TABLE_SIZE];
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    node_table[i] = NULL;
  }

  char parent_code[4];
  char child_code[4];

  while (scanf("%3s)%3s", parent_code, child_code) != EOF) {
    struct TreeNode* node = malloc(sizeof(struct TreeNode));

    strcpy(node->code, child_code);
    strcpy(node->parent_code, parent_code);
    node->height = -1;
    assert(insert_node(node_table, node) != 0);
  }

  compute_heights(node_table, ROOT_CODE);

  int sum = sum_heights(node_table);
  printf("The sum of all node heights is: %d\n", sum);

  return 0;
}
