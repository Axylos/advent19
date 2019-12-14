#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <machine.h>
#include <string.h>
#include <amp_chain.h>
#include <io.h>


int main(int argc, char* argv[]) {
  int size = 0;
  long* list = ingest(&size);
  int max = -1;
  int phases[] = { 1, 2, 3, 4, 0 };
  int max_signal = find_max_signal(phases, 0, 4, list, size, &max);
  printf("%d\n", max_signal);
  assert(max_signal == 272368);

  printf("the max signal is: %d\n", max_signal);
  return 0;
}
