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

int reader_extended() {
  return 5;
}

int eval_input(int(*reader)()) {
  FILE* fp = fopen("input.txt", "r");
  if (!fp) {
    perror("file open failed");
    return EXIT_FAILURE;
  }
  int size;
  int* list = ingest(&size, fp);
  fclose(fp);

  struct Machine* machine = init_machine(list, size, reader, writer);
  printf("FIRST RUN:\n");
  run(machine);

  return 0;
}

int main(int argc, char* argv[]) {

  printf("RUNNING FIRST PART\n");
  eval_input(reader);

  printf("PART DEUX RUN:\n");
  eval_input(reader_extended);
  return 0;
}
