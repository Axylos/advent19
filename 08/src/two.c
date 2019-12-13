#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WIDTH 25
#define HEIGHT 6
#define LEN 150

int main(int argc, char* argv[]) {
  int val = 0;
  int buf[LEN];
  char ch[1];
  memset(buf, -1, LEN * sizeof(int));

  int count = 0;
  int idx = 0;
  while(scanf("%1s", ch) != EOF) {
    count++;
    val = atoi(ch);
    if (val >= 3 || val < 0) {
      printf("count: %d\n", count);
      printf("bad val: %d idx: %d\n", val, idx);
    }
    assert(val > -1);
    assert(val < 3);

    assert(idx > -1);
    assert(idx < 150);
    if (buf[idx] == -1) {
      buf[idx] = val;
    } else if (buf[idx] == 2) {
      buf[idx] = val;
    }

    idx += 1;
    idx %= LEN; 
  }
  puts("here\n");
  for (int i = 0; i < LEN; i++) {
    if (i % WIDTH == 0) {
      printf("\n");
    }

    assert(buf[i] == 1 || buf[i] == 0);
    switch(buf[i]) {
      case 1:
        printf("\033[0;31m");
        break;
      case 0:
        printf("\033[0;32m");
        break;
    }

    printf("%d ", buf[i]);
  }

  printf("\n\n\n");
  return 0;
}
