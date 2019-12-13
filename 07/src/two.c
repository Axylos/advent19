#include <stdio.h>
#include <assert.h>
#include <amp_loop.h>

void test_one() {
  int prog[] = {
    3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
    27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5
  };
  int prog_size = sizeof(prog) / sizeof(int);
  int phases[] = { 9,8,7,6,5 };
  struct Executioner* ex = init_executioner(prog, prog_size);
  int output = compute_val(ex, phases);
  printf("output: %d\n", output);
  assert(output == 139629729);
}

void test_two() {
  int phases[] = { 9,7,8,5,6 };
  int prog_size = 0;
  int prog[] = {
    3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
    -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
    53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10
  };
  prog_size = sizeof(prog) / sizeof(int);
  struct Executioner* ex = init_executioner(prog, prog_size);
  int output = compute_val(ex, phases);
  printf("output: %d\n", output);
  assert(output == 18216);

}

int main(int argc, char* argv[]) {
  test_one();
  test_two();
  return 0;
}
