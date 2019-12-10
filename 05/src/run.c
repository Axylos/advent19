#include <assert.h>
#include <stdbool.h>
#include <machine.h>
#include <digest.h>
#include <stdio.h>
#include <stdlib.h>


int eval_input() {
  FILE* fp = fopen("input.txt", "r");
  if (!fp) {
    perror("file open failed");
    return EXIT_FAILURE;
  }
  int size;
  int* list = ingest(&size, fp);
  fclose(fp);

  struct Machine* machine = init_machine(list, size, NULL);
  printf("FIRST RUN:\n");
  run(machine);
  free_machine(machine);

  return 0;
}

int main(int argc, char* argv[]) {

  printf("RUNNING FIRST PART\n");
  eval_input();

  printf("PART DEUX RUN:\n");
  eval_input();
  return 0;
}
