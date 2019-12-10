#ifndef FILE_TREE_SEEN
#define FILE_TREE_SEEN

#define H_TABLE_SIZE 50
#include <stdio.h>
#include <stdlib.h>
#include <nodes.h>

void compute_heights(struct ListNode* table[H_TABLE_SIZE], char root[4]);
int sum_heights(struct ListNode* table[H_TABLE_SIZE]);
int find_transfer_dist(char a[4], char b[4], struct ListNode* table[H_TABLE_SIZE]);
int insert_node(struct ListNode* table[H_TABLE_SIZE], struct TreeNode* node);
#endif
