#include "utils/utils.h"
#include <stdbool.h>
#include <stdio.h>

int chars_are_unique(char *Str, int len) {
  bool char_hash[256] = {false};

  for (int i = 0; i < len; i++) {
    if (char_hash[(int)Str[i]])
      return false;

    char_hash[(int)Str[i]] = true;
  };

  return true;
}

int main() {
  char str[] = "abcdef";
  int len = sizeof(str) / sizeof(str[0]);

  if (chars_are_unique(str, len)) {
    printf("Unique!\n");
    return 0;
  } else {
    printf("Not unique.\n");
    return 1;
  }
}
