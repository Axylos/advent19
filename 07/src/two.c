#include <stdio.h>
#include <amp_loop.h>

int main(int argc, char* argv[]) {
  int prog_size = 0;
  int* prog = ingest(&prog_size);
  int phases[] = { 9,8,7,6,5 };
  struct Executioner* ex = init_executioner(prog, prog_size);
  int output = compute_val(ex, phases);
  printf("output: %d\n", output);
  return 0;
}
