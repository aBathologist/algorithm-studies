#include "utils/utils.h"
#include <stdbool.h>
#include <stdio.h>

/* Write a method to decide if two strings are anagrams or not. */

bool are_anagrams(char str_a[], char str_b[]) {
  char char_counts[256] = {0};

  int a, b;

  for (a = b = 0; str_a[a] != '\0' && str_b[b] != '\0'; a++, b++) {
    ++char_counts[(int)str_a[a]];
    --char_counts[(int)str_b[b]];
  }

  if (str_a[a] != '\0' || str_b[b] != '\0')
    return false;

  for (int i = 0; i < 256; i++) {
    if (char_counts[i] != 0)
      return false;
  }

  return true;
}

int main() {
  int results = 1;
  test("is anagram", are_anagrams("abcdef", "fedcba"), results);
  test("is not angaram", !are_anagrams("abc", "abcd"), results);
  return results;
}
