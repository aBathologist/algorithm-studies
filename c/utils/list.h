#ifndef __LIST_H_
#define __LIST_H_
#include <stdbool.h>

typedef struct cell *list;

list nil();
bool is_empty(list xs);
int list_length(list xs);
bool is_member(list xs, int x);

list singleton_list(int x);
list cons(int x, list xs);
list tail(list xs);
int head(list xs);

list list_remove(list xs, int x);

int list_nth(list xs, int n);

void iter_list(void (*f)(int), list xs);
void print_list(list xs);
void free_list(list xs);

bool lists_equal(list xs, list ys);
list list_of_array(int *arr, int len);
#endif // __LIST_H_
