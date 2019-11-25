#include "utils/utils.h"
#include <assert.h>

int main() {
  int result = 1;
  test("is substring prefix", is_substring("abc", "abcdef"), result);
  test("is substring suffix", is_substring("def", "abcdef"), result);
  test("is substring infix", is_substring("cde", "abcdef"), result);
  test("is substring empty", is_substring("", "abcdef"), result);
  test("is substring false 1", !is_substring("aboo", "abcdef"), result);
  test("is substring false 2", !is_substring("aboo", ""), result);
  return result;
}
