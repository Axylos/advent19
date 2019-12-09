#include <assert.h>
#include <stdbool.h>
#include <machine.h>
#include <digest.h>
#include <stdio.h>
#include <stdlib.h>

void writer(int val) {
  printf("got some output: %d\n", val);
}

int reader() {
  return 1;
}

int main(int argc, char* argv[]) {
  FILE* fp = fopen("input.txt", "r");
  if (!fp) {
    perror("file open failed");
    return EXIT_FAILURE;
  }
  int size;
  int* list = ingest(&size, fp);
  fclose(fp);

  struct Machine* machine = init_machine(list, reader, writer);
  run(machine);

  return 0;
}
