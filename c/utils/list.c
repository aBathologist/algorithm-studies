#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MALLOC_CELL(cellptr)                                                   \
  {                                                                            \
    if (!(cellptr = malloc(sizeof(int)))) {                                    \
      fprintf(stderr, "Insufficient memory during list creation");             \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  }

typedef struct cell {
  int val;
  struct cell *next;
} cell_t;

typedef struct cell *list;

list nil() {
  list empty = NULL;
  return empty;
}

bool is_empty(list xs) { return (xs == NULL); }

list cons(int x, list xs) {
  cell_t *new_cell;
  MALLOC_CELL(new_cell);

  new_cell->val = x;
  new_cell->next = xs;
  return new_cell;
}

list singleton_list(int x) { return cons(x, nil()); }

list tail(list xs) {
  if (xs == NULL) {
    fprintf(stderr, "tail of empty list");
    exit(EXIT_FAILURE);
  }
  return xs->next;
}

int head(list xs) {
  if (xs == NULL) {
    fprintf(stderr, "head of empty list");
    exit(EXIT_FAILURE);
  }
  return xs->val;
}

list list_remove(list xs, int x) {
  list xs_ = xs;
  if (head(xs_) == x)
    return tail(xs);

  while (!is_empty(xs_)) {
    if (head(tail(xs_)) == x) {
      list remove = tail(xs_);
      xs_->next = tail(tail(xs_));
      free(remove);
      return xs;
    }
    xs_ = tail(xs_);
  }
  return xs;
}

void iter_list(void (*f)(int), list xs) {
  if (!is_empty(xs)) {
    f(head(xs));
    iter_list(f, tail(xs));
  }
}

void print_int(int i) { printf("%d ", i); }

void print_list(list xs) {
  printf("[ ");
  iter_list(print_int, xs);
  printf("]\n");
}

void free_cell(cell_t *cellptr) { free(cellptr); }

void free_list(list xs) {
  while (xs != NULL) {
    list next = tail(xs);
    free_cell(xs);
    xs = next;
  }
}

int list_length(list xs) {
  int len = 0;
  while (!is_empty(xs)) {
    xs = tail(xs);
    len++;
  }
  return len;
}

int list_nth(list xs, int n) {
  while (n != 0 && !is_empty(xs)) {
    n--;
    xs = tail(xs);
  }

  if (is_empty(xs)) {
    // TODO Proper handling of error condition
    return -1;
  } else {
    return head(xs);
  }
}

int *array_of_list(list xs) {
  int len = list_length(xs);
  int *arr = malloc(len * sizeof(int));

  if (arr == NULL) {
    fprintf(stderr, "Insufficient memory converting list to array");
    exit(EXIT_FAILURE);
  } else {
    for (int i = 0; i < len; i++) {
      arr[i] = head(xs);
      xs = tail(xs);
    }
  }

  return arr;
}

list list_of_array(int *arr, int len) {
  list xs = nil();
  for (int i = (len - 1); i >= 0; i--) {
    xs = cons(arr[i], xs);
  }
  return xs;
}

bool lists_equal(list xs, list ys) {
  bool result = true;
  while (!is_empty(xs) && !is_empty(ys)) {
    result = result && head(xs) == head(ys);
    xs = tail(xs);
    ys = tail(ys);
  }

  return result && is_empty(xs) && is_empty(ys);
}

bool is_member(list xs, int x) {
  while (!is_empty(xs)) {
    if (head(xs) == x)
      return true;
    xs = tail(xs);
  }
  return false;
}
/* } */
