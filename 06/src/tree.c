#include <tree.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

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
int find_node_height(struct ListNode* table[H_TABLE_SIZE], struct TreeNode* node, char targ_code[4]) {
  if (strcmp(node->parent_code, targ_code) == 0) {
    return 1;
  } else if (node->height > -1) {
    return node->height;
  } else {
    struct TreeNode* parent_node = table_lookup(table, node->parent_code); 
    assert(parent_node != NULL);
    return find_node_height(table, parent_node, targ_code) + 1;
  }

  assert(0);
  return 0;
}


void compute_heights(struct ListNode* table[H_TABLE_SIZE], char root[4]) {
  for (int i = 0; i < H_TABLE_SIZE; i++) {
    struct ListNode* head = table[i];
    while (head != NULL) {
      struct TreeNode* node = table_lookup(table, head->val->code);
      int height = find_node_height(table, node, root);
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

struct TreeNode* find_common_ancestor(struct TreeNode* a, struct TreeNode* b,
    struct ListNode* table[H_TABLE_SIZE]) {
  struct ListNode* seen_nodes_by_a[H_TABLE_SIZE];
  struct ListNode* seen_nodes_by_b[H_TABLE_SIZE];

  for (int i = 0; i < H_TABLE_SIZE; i++) {
    seen_nodes_by_a[i] = NULL;
    seen_nodes_by_b[i] = NULL;
  }
  bool match_found = false;
  while(!match_found) {
    if (a != NULL) {
      insert_node(seen_nodes_by_a, a);
      if (table_lookup(seen_nodes_by_b, a->code)) {
        return a;
      }
    }

    if (b != NULL) {
      insert_node(seen_nodes_by_b, b);
      if (table_lookup(seen_nodes_by_a, b->code)) {
        return b;
      }
    }

    if (a == NULL && b == NULL) {
      assert(0);
    }

    a = table_lookup(table, a->parent_code);
    b = table_lookup(table, b->parent_code);

  }

  return NULL;
}

int find_transfer_dist(char a[4], char b[4], struct ListNode* table[H_TABLE_SIZE]) {
  struct TreeNode* a_node = table_lookup(table, a);
  struct TreeNode* b_node = table_lookup(table, b);

  struct TreeNode* a_parent = table_lookup(table, a_node->parent_code);
  struct TreeNode* b_parent = table_lookup(table, b_node->parent_code);

  struct TreeNode* ancestor = find_common_ancestor(a_parent, b_parent, table);
  printf("common ancestor: %s\n", ancestor->code);
  int a_height = find_node_height(table, a_parent, ancestor->code);
  int b_height = find_node_height(table, b_parent, ancestor->code);

  return a_height + b_height;
}

