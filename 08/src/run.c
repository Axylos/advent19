#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char* argv[]) {
  char ch;
  int product = -1;
  int min = -1;
  int count_zeros = 0;
  int count_ones = 0;
  int count_twos = 0;
  int pos = 1;
  int layer = 0;
  while((ch = getchar()) != EOF) {
    int val = atoi(&ch);
    if (val == 1) {
      count_ones++;
    } else if (val == 2) {
      count_twos++;
    } else if (val == 0) {
      count_zeros++;
    }

    int current_layer = pos++ / 150;
    if (current_layer != layer) {
      layer = current_layer;
      if (min == -1 || min > count_zeros) {
        min = count_zeros;
        product = count_ones * count_twos;
      }

      count_zeros = 0;
      count_ones = 0;
      count_twos = 0;
    }
  }
  printf("the min product is: %d\n", product);

  assert(product == 2413);
  return 0;
}
