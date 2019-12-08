#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

void parse_input(int* a, int* b) {
  scanf("%d-%d", a, b);
}

struct Node {
  int val;
  struct Node* next;
};

bool is_sorted(struct Node* head) {
  int n = head->val;
  while (head != NULL) {
    if (head->val < n) {
      return false;
    }
    n = head->val;
    head = head->next;
  }

  return true;
}
bool list_has_val(struct Node* head, int val) {
  while (head != NULL) {
    if (head->val == val) {
      return true;
    }

    head = head->next;
  }

  return false;
}

void append_node(struct Node* head, struct Node* node) {
  while (head->next != NULL) {
    head = head->next;
  }

  head->next = node;
}

bool is_valid(int n) {
  bool double_seen = false;
  struct Node* head = NULL;
  while (n > 0) {
    struct Node* node = malloc(sizeof(struct Node));
    int val = n % 10;
    n /= 10;
    node->val = val;
    if (head == NULL) {
      head = node;
    } else {
      if (list_has_val(head, node->val)) {
        double_seen = true;
      }

      append_node(head, node);
    }
  }

  return double_seen && is_sorted(head);
}

bool is_valid_part_deux(int n) {
  bool double_seen = false;
  int step = -1;
  int prev = -1;
  bool is_step_odd = false;

  while (n > 0) {

    prev = step;
    step = n % 10;
    n /= 10;
    if (prev > -1 && prev < step) {
      return false;
    }

    if (prev != step) {
      if (prev > 0 && is_step_odd == false) {
        double_seen = true;
      }
      is_step_odd = true;
    } else {
      is_step_odd = !is_step_odd;
    }
  }

  return double_seen;
}
int get_valid_pw_count_in_range(int a, int b, bool(*validator)(int a)) {
  int sum = 0;
  for (int i = a; i <= b; i++) {
    if (validator(i)) {
      sum += 1;
    }
  }

  return sum;
}

int main(int argc, char* argv[]) {
  int a;
  int b;

  parse_input(&a, &b);
  assert(is_valid(10) == false);
  assert(is_valid(11));

  assert(is_valid(111111));
  assert(!is_valid(223450));
  assert(!is_valid(123789));

  assert(is_valid_part_deux(112233));
  assert(!is_valid_part_deux(123444));
  assert(is_valid_part_deux(111122));
  //assert(is_valid_part_deux(111111));


  int sum = get_valid_pw_count_in_range(a, b, is_valid);
  printf("the sum of valid pws is: %d\n", sum);

  int sum2 = get_valid_pw_count_in_range(a, b, is_valid_part_deux);
  printf("the answer to part II is: %d\n", sum2);
  return 0;
}
