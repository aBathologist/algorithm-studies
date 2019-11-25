#include "utils/utils.h"
#include <stdbool.h>

/*
Write an algorithm such that if an element in an MxN matrix is 0, its entire row
and column is set to 0.

  0 1 2
 +-----
0|1 2 3
1|0 2 3
2|1 2 3

f(1,0) -> (0,0) (1, 0) (2, 0) * (1, 0), (1, 1), (1, 2)

  0 1 2
 +-----
0|1 2 3
1|1 0 3
2|1 2 3

f(1, 1) -> (0,1) (1, 1) (2, 1) * (1, 0) (1, 1) (1, 2)
*/

void zero_out(int n, int m[n][n]) {
  int x_zeroed[n];
  int y_zeroed[n];

  for (int i = 0; i < n; i++) {
    y_zeroed[i] = false;
    x_zeroed[i] = false;
  }

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      if (m[y][x] == 0) {
        y_zeroed[y] = true;
        x_zeroed[x] = true;
      }
    }
  }

  for (int y = 0; y < n; y++) {
    for (int x = 0; x < n; x++) {
      if (y_zeroed[y] || x_zeroed[x]) {
        m[y][x] = 0;
      }
    }
  }
}

int main() {
  int m[3][3] = {{1, 2, 3}, {0, 2, 3}, {1, 2, 3}};

  zero_out(3, m);
  printf("1\n");
  print_matrix(3, m);

  int m1[3][3] = {{1, 2, 3}, {1, 0, 3}, {1, 2, 3}};

  zero_out(3, m1);
  printf("2\n");
  print_matrix(3, m1);
  return 0;
}
