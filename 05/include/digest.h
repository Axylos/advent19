#include <machine.h>
#include <stdlib.h>
#include <stdio.h>

int* ingest(int* size, FILE* fd) {
  int* list = calloc(OP_LIST_SIZE, sizeof(int));
  int capacity = OP_LIST_SIZE;
  *size = 0;
  int i;
  while(fscanf(fd, "%d,?", &i) != EOF) {
    if (*size == capacity) {
      capacity *= 2;
      list = realloc(list, capacity * sizeof(int));
    }

    list[(*size)++] = i;
  }

  return list;
}

