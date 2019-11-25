#include "utils/utils.h"
#include <stdio.h>

/* Write code to reverse a C-Style String. (C-String means that “abcd” is
represented as five characters, including the null character.) */

void reverse(char str[], int len) {
  int i, j;
  char tmp;
  for (i = 0, j = len - 2; i < j; i++, j--) {
    tmp = str[i];
    str[i] = str[j];
    str[j] = tmp;
  }
}

int main() {
  char str[] = "abcd";
  int len = sizeof(str) / sizeof(str[0]);

  printf("original: %s\n", str);
  reverse(str, len);
  printf("reversed: %s\n", str);
}
