#ifndef FILE_NODE_H_SEEN
#define FILE_NODE_H_SEEN
struct ListNode {
  struct TreeNode* val;
  struct ListNode* next;
};



struct TreeNode {
  int height;
  char code[4];
  char parent_code[4];
};

#endif
