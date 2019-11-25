#include "utils/utils.h"
#include <stdio.h>

/* Design an algorithm and write code to remove the duplicate characters in a */
/* string without using any additional buffer. NOTE: One or two additional */
/* variables are fine. An extra copy of the array is not. */

/* abcdeef00
    ij
     k
*/
void remove_dups(char str[]) {
  int i, j, k;
  for (i = 0; str[i] != '\0'; i++) {
    for (j = k = i + 1; str[j] != '\0'; j++) {
      if (str[i] == str[j]) {
        str[j] = '\0';
      } else if (j != k) {
        str[k++] = str[j];
        str[j] = '\0';
      } else {
        k++;
      }
    }
  }
}

int main() {
  char str[] = "aabcedeaf";

  printf("original: %s\n", str);
  remove_dups(str);
  printf("deduped: %s\n", str);
}
