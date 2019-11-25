#include "utils/utils.h"

/* Given an image represented by an NxN matrix, where each pixel in the image is
4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
place? */

/*
   0 1 2       0 1 2
 0 a b c     0 g d a
 1 d e f --> 1 h e d
 2 g h i     2 i f c

 n x n where n = 3

 y, x    y, x
 0, 0 -> 0, 2
 0, 1 -> 1, 2
 0, 2 -> 2, 2

 1, 0 -> 0, 1
 1, 1 -> 1, 1
 1, 2 -> 2, 1

 2, 0 -> 0, 0
 2, 1 -> 1, 0
 2, 2 -> 2, 0

 f : (int, int) -> (int, int) = fun (y, x) -> (x, (n - 1) - y)

 e.g.,
 f (0, 2) = (2, (3 - 1) - 0) = (2, 2)
 f (2, 1) = (1, (3 - 1) - 2) = (1, 0)
 */
void print_image(int n, int m[n][n][3]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      print_array(m[i][j], 3);
      printf(" ");
    }
    printf("\n");
  }
}

void copy_pixel(int a[3], int b[3]) {
  for (int i = 0; i < 3; i++) {
    b[i] = a[i];
  }
}

struct coords {
  int y;
  int x;
};

void flip_coords(int n, int y, int x, struct coords *c) {
  c->y = x;
  c->x = (n - 1) - y;
}

void rotate_90(int n, int a[n][n][3], int b[n][n][3]) {
  int y, x;
  struct coords c;

  for (y = 0; y < n; y++) {
    for (x = 0; x < n; x++) {
      flip_coords(n, y, x, &c);
      copy_pixel(a[y][x], b[c.y][c.x]);
    }
  }
}

/*

  last =
  next = a

   0 1 2
 0 a b c
 1 d e f
 2 g h i

 last = next = a
 next = a[0][2] = c
 a[0][2] = last

   0 1 2
 0 a b a
 1 d e f
 2 g h i

 last = next = c
 next = a[2][2] = i
 a[2][2] = last

   0 1 2
 0 a b a
 1 d e f
 2 g h c

 last = next = i
 next = a[0][2] = g
 a[0][2] = last

   0 1 2
 0 a b a
 1 d e f
 2 i h c

 last = next = g
 next = a[0][2] = a
 a[0][0] = last

   0 1 2
 0 g b a
 1 d e f
 2 i h c
  */
void rotate_90_inplace(int n, int m[n][n][3]) {
  struct coords c;
  int last[3], next[3];

  /* Used to narrow scope of X iterations as we descend into interior of matrix
   */
  int start_offset = 0;
  int end_offset = n - 1;

  for (int y = 0; start_offset < end_offset; y++) {
    c.y = y;

    for (int x = start_offset; x < end_offset; x++) {
      c.x = x;
      copy_pixel(m[c.y][c.x], next);

      for (int i = 0; i < 4; i++) {
        copy_pixel(next, last);
        flip_coords(n, c.y, c.x, &c);
        copy_pixel(m[c.y][c.x], next);
        copy_pixel(last, m[c.y][c.x]);
      }
    }

    start_offset++;
    end_offset--;
  }
}

int main() {
  int img_a[3][3][3] = {{{0, 0, 0}, {0, 1, 0}, {0, 2, 0}},
                        {{1, 0, 1}, {1, 1, 0}, {1, 2, 0}},
                        {{2, 0, 1}, {2, 1, 0}, {2, 2, 0}}};

  int img_b[3][3][3];

  int img_4_a[4][4][3] = {{{0, 0, 0}, {0, 1, 0}, {0, 2, 0}, {0, 3, 0}},
                          {{1, 0, 1}, {1, 1, 0}, {1, 2, 0}, {1, 3, 0}},
                          {{2, 0, 1}, {2, 1, 0}, {2, 2, 0}, {2, 3, 0}},
                          {{3, 0, 1}, {3, 1, 0}, {3, 2, 0}, {3, 3, 0}}};

  int img_4_b[4][4][3];

  printf("3 x 3 Before:\n");
  print_image(3, img_a);

  rotate_90(3, img_a, img_b);

  printf("3 x 3 After:\n");
  print_image(3, img_b);

  printf("3 x 3 In place before:\n");
  print_image(3, img_a);
  rotate_90_inplace(3, img_a);
  printf("3 x 3 In place after:\n");
  print_image(3, img_a);

  printf("4 x 4 Before:\n");
  print_image(4, img_4_a);

  rotate_90(4, img_4_a, img_4_b);

  printf("4 x 4 After:\n");
  print_image(4, img_4_b);

  printf("4 x 4 In place before:\n");
  print_image(4, img_4_a);
  rotate_90_inplace(4, img_4_a);
  printf("4 x 4 In place after:\n");
  print_image(4, img_4_a);
}
