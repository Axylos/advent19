#include <assert.h>
#include <stdbool.h>
#include <machine.h>
#include <digest.h>
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

int eval_input() {
  FILE* fp = fopen("input.txt", "r");
  if (!fp) {
    perror("file open failed");
    return EXIT_FAILURE;
  }
  int size;
  long* list = ingest(&size, fp);
  fclose(fp);

  struct Machine* machine = init_machine(list, size, NULL);
  run(machine);
  free(machine);

  return 0;
}

int main(int argc, char* argv[]) {

  printf("RUNNING FIRST PART\n");
  input = 1;
  eval_input();
  assert(output == 13787043);

  printf("PART DEUX RUN:\n");
  input = 5;
  eval_input();
  assert(output == 3892695);
  return 0;
}
