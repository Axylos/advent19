#include <assert.h>
#include <amp_loop.h>

void test_computation() {
  int prog[] = {
    3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
    27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5
  };

  int phases[] = { 9,8,7,6,5 };

  int prog_size = sizeof(prog) / (sizeof(int));
  struct Executioner* ex = init_executioner(prog, prog_size);

  int val = compute_val(ex, phases);

  printf("val: %d\n", val);
  assert(val == 139629729);
}
int main(int argc, char* argv[]) {
  test_computation();
  return 0;
}
