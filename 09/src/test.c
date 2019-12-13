#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char str[] = "1125899906842624";
  long foo = 0;
  sscanf(str, "%ld", &foo);
  printf("%ld\n", foo);
  puts("here");
  return 0;
}
