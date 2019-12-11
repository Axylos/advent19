#include <stdio.h>
#include <stdlib.h>
#include <machine.h>
#include <string.h>
#include <amp_chain.h>

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


int main(int argc, char* argv[]) {
  puts("called");
  int size = 0;
  int* list = ingest(&size);

  int arg = 10;
  struct Machine* m = init_machine(list, size, (void*)&arg);
  run(m);
  printf("%d\n", size);

  int nums[N_PHASES] = { 1, 2, 3, 4, 5 };
  int i;
  struct Machine* machine = init_machine(list, size, &i);
  machine->reg_size = size;
  find_maximal_signal(nums, 0, 4, list, size, machine);
  return 0;
}
