#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
#define TARGET 19690720

#define HALT 99
#define ADD 1
#define MULT 2

int* ingest(int* size) {

  int* list = calloc(SIZE, sizeof(int));
  int capacity = SIZE;
  int _size = 0;
  int i;
  while(scanf("%d,?", &i) != EOF) {
    if (_size == capacity) {
      capacity *= 2;
      list = realloc(list, capacity * sizeof(int));
    }


    list[_size++] = i;
  }

  *size = _size;
  return list;
}


int run(int* ops, int size, int x, int y) {
  ops[1] = x;
  ops[2] = y;
  int idx = 0;
  while(idx < size) {
    int op = ops[idx++];
    int a = ops[idx++];
    int b = ops[idx++];
    int addr = ops[idx++];

    switch(op) {
      case HALT: return ops[0];
                 break;
      case ADD: ops[addr] = ops[a] + ops[b];
                break;
      case MULT: ops[addr] = ops[a] * ops[b];
                 break;
    }
  }

  return ops[0];
}

int* copy_arr(int* arr, int* targ, int size) {
  for (int i = 0; i < size; i++) {
    targ[i] = arr[i];
  }

  return targ;
}

int main(int argc, char* argv[]) {
  int size = 0;
  int* ops = ingest(&size);
  int* tmp_ops = calloc(size, sizeof(int));
  copy_arr(ops, tmp_ops, size);

  int first_answer = run(tmp_ops, size, 12, 2);
  printf("the first answer is: %d\n", first_answer);

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      copy_arr(ops, tmp_ops, size);
      int ret = run(tmp_ops, size, i, j);
      if (ret == TARGET) {
        printf("The second answer is %d\n", 100 * i + j);
      }
    }
  }
  return 0;

}
