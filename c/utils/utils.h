#ifndef __UTILS_H_
#define __UTILS_H_
#include <stdbool.h>
#include <stdio.h>

void print_array(int arry[], int len);
void print_matrix(int n, int m[n][n]);
bool is_substring(char sub[], char str[]);
bool arrays_equal(int *a, int *b, int len);

void test(char test_name[], bool test_result, bool results);

#endif // __UTILS_H_
