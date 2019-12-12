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
  return 9;

}

int test_prog(char file_name[]) {
  FILE* fp = fopen(file_name, "r");
  if (!fp) {
    perror("file open failed");
    return EXIT_FAILURE;
  }
  int size;
  int* list = ingest(&size, fp);
  fclose(fp);

  int i = 9;
  struct Machine* machine = init_machine(list, size, &i);
  run(machine);

  return 0;
}

int main(int argc, char* argv[]) {
  //assert(test_prog("test_progs/01.txt") == 0);
  //assert(test_prog("test_progs/02.txt") == 0);
  
  // test if eq 8
  //assert(test_prog("test_progs/03.txt") == 0);
  //test_prog("test_progs/05.txt");
  
  // test if lt 8
  //test_prog("test_progs/06.txt");
  //test_prog("test_progs/04.txt");
  
  // test if input is 0 and print 0 if so
  //test_prog("test_progs/07.txt");
  //test_prog("test_progs/08.txt");

  // test <=> 8
  test_prog("test_progs/09.txt");
  return 0;
}
