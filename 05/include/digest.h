#include <machine.h>
#include <stdlib.h>
#include <stdio.h>

long* ingest(int* size, FILE* fd) {
  long* list = calloc(OP_LIST_SIZE, sizeof(long));
  int capacity = OP_LIST_SIZE;
  *size = 0;
  int i;
  while(fscanf(fd, "%d,?", &i) != EOF) {
    if (*size == capacity) {
      capacity *= 2;
      list = realloc(list, capacity * sizeof(long));
    }

    list[(*size)++] = i;
  }

  return list;
}

