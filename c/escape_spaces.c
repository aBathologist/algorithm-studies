#include "utils/utils.h"
#include <string.h>

/* Write a method to replace all spaces in a string with ‘%20’. */

int escaped_length(char *str) {
  int spaces = 0;
  int i;

  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ')
      spaces++;
  }

  return i + (spaces * 3);
}

void escape_spaces(char *str, char *escaped) {
  int len = 0;
  int n_spaces = 0;

  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ')
      n_spaces++;
    len++;
  }

  int j;
  for (i = j = 0; str[i] != '\0'; i++) {
    if (str[i] == ' ') {
      escaped[j++] = '%';
      escaped[j++] = '2';
      escaped[j++] = '0';
    } else {
      escaped[j++] = str[i];
    }
  }

  escaped[j] = '\0';
}

int main() {
  int len;

  char str1[] = "  ";
  len = escaped_length(str1);
  char str2[len];
  escape_spaces(str1, str2);
  int r1 = (strncmp(str2, "%20%20", len) == 0);

  char str3[] = "test yep";
  len = escaped_length(str3);
  char str4[len];
  escape_spaces(str3, str4);
  printf("%s\n", str4);
  int r2 = (strncmp(str4, "test%20yep", len) == 0);

  char str5[] = "";
  escape_spaces("", str5);
  int r3 = (strncmp(str5, "", 1) == 0);

  int result = 1;
  test("escapes 1", r1, result);
  test("escapes 2", r2, result);
  test("escapes 3", r3, result);
  return result;
}
