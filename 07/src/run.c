#include <stdio.h>
#include <stdlib.h>
#include <machine.h>
#include <string.h>


struct Store {
  int* phases;
  int current_val;
  int amp_n;
};
#define SIZE 10
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

void swap(int* a, int* b) {
  int tmp;
  tmp = *a;
  *a = *b;
  *b = tmp;
}

int compute_output(int phases[5], int program[], int size, struct Machine* machine) {
  return 0;
}

void permute(int phases[5], int l, int r, int list[], int size, struct Machine* machine) {
  if (l == r) {
    int vals[size];
    memcpy(machine->regs, list, size);
    
    struct Store store = {
      phases,
      0,
      0,
    };
    machine->ip = 0;
    machine->data_ptr = (void*)&store;
    int output = compute_output(phases, list, size, machine);
    printf("output: %d\n", output);
  } else {
    for (int i = l; i <= r; i++) {
      swap((phases + l), (phases + i));
      permute(phases, l + 1, r, list, size, machine);
      swap((phases+ l), (phases + i));
    }
  }
}

int main(int argc, char* argv[]) {
  puts("called");
  int size = 0;
  int* list = ingest(&size);

  int arg = 10;
  struct Machine* m = init_machine(list, size, (void*)&arg);
  run(m);
  printf("%d\n", size);

  int nums[5] = { 1, 2, 3, 4, 5 };
  int i;
  struct Machine* machine = init_machine(list, size, &i);
  machine->reg_size = size;
  permute(nums, 0, 3, list, size, machine);
  return 0;
}
