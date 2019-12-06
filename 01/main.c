#include <stdio.h>
#include <assert.h>

int fuel_helper(int mass) {
  return (mass / 3) - 2;
}

int compute_fuel(int mass) {
  int m = mass;
  int sum = 0;

  while (m > 0) {
    m = fuel_helper(m);
    if (m > 0) {
      sum += m;
    }
  }

  return sum;
}

int main (int argc, char* argv[]) {

  char str[50];
  int i;
  int sum_mass = 0;
  while (fscanf(stdin, "%d\n", &i) > 0) {
    int mass = (i / 3) - 2;
    sum_mass += mass;

    int extra_fuel_mass = compute_fuel(mass);
    sum_mass += extra_fuel_mass;
  }

  printf("The sum of the module masses is: %d\n", sum_mass);

  return 0;
}
