#include "utils.h"
#include <stdbool.h>
#include <stdio.h>

void print_array(int arr[], int len) {
  printf("{");
  for (int i = 0; i < len; i++) {
    printf("%d", arr[i]);
    if (i < len - 1)
      printf(", ");
  }
  printf("}");
}

void print_matrix(int n, int m[n][n]) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d ", m[i][j]);
    }
    printf("\n");
  }
}

bool arrays_equal(int *a, int *b, int len) {
  bool result = true;
  for (int i = 0; i < len; i++) {
    result = result && (a[i] == b[i]);
  }
  return result;
}

bool is_substring(char sub[], char str[]) {
  int i, j, s;

  if (sub[0] == '\0')
    return true;

  for (i = 0; str[i] != '\0'; i++) {
    if (sub[0] == str[i]) {
      for (j = 0, s = i; str[s] != '\0' && sub[j] != '\0'; j++, s++) {
        if (sub[j] != str[s])
          break;
      }

      if (sub[j] == '\0')
        return true;
    }
  }

  return false;
}

void test(char test_name[], bool test_result, bool results) {
  if (test_result) {
    printf("[OK] Test '%s' passed\n", test_name);
  } else {
    printf("[ERR] Tests '%s' failed\n", test_name);
  }
  results = results && results;
}
