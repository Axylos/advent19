#include <assert.h>
#include <stdbool.h>
#include <machine.h>
#include <digest.h>
#include <stdio.h>
#include <stdlib.h>

void writer(int val) {
  printf("it happened: %d\n", val);
}

int reader() {
  return 99;
}

int test_simple_prog() {
  FILE* fp = fopen("test_progs/01.txt", "r");
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

int test_other_simple_prog() {
  FILE* fp = fopen("test_progs/02.txt", "r");
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

int main(int argc, char* argv[]) {
  test_simple_prog();
  assert(test_other_simple_prog() == 0);
  return 0;
}
