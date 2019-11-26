#include "utils/list.h"
#include "utils/utils.h"
#include <assert.h>

void list_tests(int *result) {
  list xs = cons(1, (cons(2, cons(3, nil()))));

  printf("Test 'can print list': ");
  print_list(xs);

  test("list length", (list_length(xs) == 3), result);
  test("list length of empty", (list_length(nil()) == 0), result);
  test("nth item of list", (list_nth(xs, 1) == 2), result);
  test("lists_equal", lists_equal(xs, xs), result);
  test("is member", is_member(xs, 2), result);
  test("is not member", !is_member(xs, 5), result);

  int arr[3] = {3, 2, 1};
  list ys = list_of_array(arr, 3);

  test("lists unequal", !lists_equal(xs, ys), result);
  test("list of array", (list_length(ys) == 3), result);

  list ys_no_2 = list_remove(ys, 2);
  list ys_no_2_ = cons(3, (cons(1, nil())));
  test("remove 2 from list", lists_equal(ys_no_2, ys_no_2_), result);

  free_list(xs);
}
int main() {

  int result = 1;
  test("is substring prefix", is_substring("abc", "abcdef"), result);
  test("is substring suffix", is_substring("def", "abcdef"), result);
  test("is substring infix", is_substring("cde", "abcdef"), result);
  test("is substring empty", is_substring("", "abcdef"), result);
  test("is substring false 1", !is_substring("aboo", "abcdef"), result);
  test("is substring false 2", !is_substring("aboo", ""), result);

  int arr[3] = {1, 2, 3};
  int arrb[3] = {1, 2, 0};
  test("arrays are equal", arrays_equal(arr, arr, 3), result);
  test("arrays are not", !arrays_equal(arr, arrb, 3), result);

  list_tests(&result);
  return result;
}
