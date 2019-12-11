#include <assert.h>
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
  int max = -1;
  int phases[] = { 1, 2, 3, 4, 0 };
  int max_signal = find_max_signal(phases, 0, 4, list, size, &max);
  assert(max_signal == 272368);

  printf("the max signal is: %d\n", max_signal);
  return 0;
}
