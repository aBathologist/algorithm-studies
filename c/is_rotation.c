#include "utils/utils.h"
#include <stdbool.h>
#include <strings.h>

/*
Assume you have a method isSubstring which checks if one word is a substring of
another. Given two strings, s1 and s2, write code to check if s2 is a rotation
of s1 using only one call to isSubstring (i.e., “waterbottle” is a rotation of
“erbottlewat”).
*/

/* - scan s2 until you find a sequence which matchs the begeinning of s1
   - count the length of the sequence until the end of s2 = len
      - if no such sequence is found, it cannot be a rotation
   - increment the pointer for s1 by len (getting the suffix of s2 after len)
   - check whether is_substring(*s1 + len, s2)
 */

bool is_rotation(char *s1, char *s2) {
  int i, j, k;

  int wrapped_len = 0;

  for (i = 0; s2[i] != '\0'; i++) {
    if (s2[i] == s1[0]) {
      for (j = 0, k = i; s2[k] == s1[j] && s2[k] != '\0' && s1[j] != '\0';
           j++, k++)
        ;
      if (s2[k] == '\0') {
        wrapped_len = j;
        break;
      }
    }
  }

  if (wrapped_len > 0) {
    s1 += wrapped_len;
    return is_substring(s1, s2);
  } else {
    return false;
  }
}

int main() {
  int result = 1;
  test("rotation 1", is_rotation("erbottlewat", "waterbottle"), result);
  test("rotation 2", is_rotation("waterbottle", "waterbottle"), result);
  test("not rotation 1", !is_rotation("spowaterbottle", "waterbottle"), result);
  test("not rotation 2", !is_rotation("water", "waterbottle"), result);
  return result;
};
